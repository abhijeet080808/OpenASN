#include "AsnParser.hh"

#include "ParseDefs.hh"
#include "ParseHelper.hh"
#include "ParseLog.hh"

#include "parser/ModuleDefinition.hh"
#include "parser/ProductionFactory.hh"
#include "spdlog/spdlog.h"

#include <fstream>
#include <iterator>
#include <sstream>

using namespace OpenASN;

std::vector<std::shared_ptr<IProduction>>
AsnParser::
Parse(const std::string& asnFilePath)
{
  SPDLOG_INFO("Parsing \"{}\"",
              asnFilePath);

  // char + line index + char index
  std::vector<std::tuple<char, size_t, size_t>> asn_file_data;
  std::vector<Word> parsed_asn_data;

  char c;
  size_t line_index = 1;
  size_t char_index = 1;

  std::ifstream asn_file(asnFilePath);

  while (asn_file.get(c))
  {
    asn_file_data.push_back(std::make_tuple(c, line_index, char_index++));
    if (c == '\n')
    {
      line_index++;
      char_index = 1;
    }
  }

  asn_file.close();

  if (asn_file_data.empty())
  {
    SPDLOG_ERROR("Parsing of empty file \"{}\" failed",
                 asnFilePath);
    return std::vector<std::shared_ptr<IProduction>>();
  }

  // remove all comments of type -- xx -- and /* xx */
  int num_single_line_comment_started = 0;
  int num_multi_line_comment_started = 0;
  for (size_t i = 0; i < asn_file_data.size(); i++)
  {
    if (num_single_line_comment_started)
    {
      if ((i + 1) < asn_file_data.size() &&
          std::get<0>(asn_file_data.at(i)) == '-' &&
          std::get<0>(asn_file_data.at(i + 1)) == '-')
      {
        num_single_line_comment_started = 0;
        asn_file_data.erase(asn_file_data.begin() + i);
        asn_file_data.erase(asn_file_data.begin() + i);
        --i;
      }
      else if (std::get<0>(asn_file_data.at(i)) == '\n')
      {
        num_single_line_comment_started = 0;
      }
      else
      {
        asn_file_data.erase(asn_file_data.begin() + i);
        --i;
      }
    }
    else if (num_multi_line_comment_started)
    {
      if ((i + 1) < asn_file_data.size() &&
          std::get<0>(asn_file_data.at(i)) == '/' &&
          std::get<0>(asn_file_data.at(i + 1)) == '*')
      {
        ++num_multi_line_comment_started;
        asn_file_data.erase(asn_file_data.begin() + i);
        asn_file_data.erase(asn_file_data.begin() + i);
        --i;
      }
      else if ((i + 1) < asn_file_data.size() &&
               std::get<0>(asn_file_data.at(i)) == '*' &&
               std::get<0>(asn_file_data.at(i + 1)) == '/')
      {
        --num_multi_line_comment_started;
        asn_file_data.erase(asn_file_data.begin() + i);
        asn_file_data.erase(asn_file_data.begin() + i);
        --i;
      }
      else
      {
        asn_file_data.erase(asn_file_data.begin() + i);
        --i;
      }
    }
    else
    {
      if ((i + 1) < asn_file_data.size() &&
          std::get<0>(asn_file_data.at(i)) == '-' &&
          std::get<0>(asn_file_data.at(i + 1)) == '-')
      {
        num_single_line_comment_started = 1;
        asn_file_data.erase(asn_file_data.begin() + i);
        asn_file_data.erase(asn_file_data.begin() + i);
        --i;
      }
      else if ((i + 1) < asn_file_data.size() &&
               std::get<0>(asn_file_data.at(i)) == '/' &&
               std::get<0>(asn_file_data.at(i + 1)) == '*')
      {
        num_multi_line_comment_started = 1;
        asn_file_data.erase(asn_file_data.begin() + i);
        asn_file_data.erase(asn_file_data.begin() + i);
        --i;
      }
      else
      {
        // not a comment
      }
    }
  }

  std::stringstream asn_file_data_ss;
  asn_file_data_ss << "File content (comments stripped):\n";
  for (size_t i = 0; i < asn_file_data.size(); i++)
  {
    asn_file_data_ss << std::get<0>(asn_file_data.at(i));
    //asn_file_data_ss << " [" << std::get<1>(asn_file_data.at(i))
    //                 << ":" << std::get<2>(asn_file_data.at(i))
    //                 << "] " << std::get<0>(asn_file_data.at(i));
  }
  SPDLOG_INFO("{}", asn_file_data_ss.str());

  std::vector<char> asn_word;
  size_t asn_word_line_index = 0;
  size_t asn_word_char_index = 0;
  int num_preceding_whitespaces = 0;

  PrecedingInfo preceding_info =
    PrecedingInfo::PRECEDED_BY_NEWLINE;

  // parse each word
  for (const auto& c : asn_file_data)
  {
    if (asn_word.empty())
    {
      if (ParseHelper::IsNewline(std::get<0>(c)))
      {
        preceding_info = PrecedingInfo::PRECEDED_BY_NEWLINE;
        continue;
      }
      else if (ParseHelper::IsWhitespace(std::get<0>(c)))
      {
        // newline has priority until the first word is reached
        // for the current line, so if it is PRECEDED_BY_NEWLINE,
        // let it remain so
        //
        // if it is already PRECEDED_BY_WHITESPACE, nothing to change
        ++num_preceding_whitespaces;
        continue;
      }
      else
      {
        asn_word.push_back(std::get<0>(c));
        asn_word_line_index = std::get<1>(c);
        asn_word_char_index = std::get<2>(c);
      }
    }
    else
    {
      if (ParseHelper::IsNewline(std::get<0>(c)))
      {
        parsed_asn_data.push_back(std::make_tuple(
            preceding_info,
            std::string(asn_word.begin(), asn_word.end()),
            SucceedingInfo::SUCCEEDED_BY_NEWLINE,
            num_preceding_whitespaces,
            asn_word_line_index,
            asn_word_char_index));
        asn_word.clear();
        num_preceding_whitespaces = 0;
        preceding_info = PrecedingInfo::PRECEDED_BY_NEWLINE;
      }
      else if (ParseHelper::IsWhitespace(std::get<0>(c)))
      {
        parsed_asn_data.push_back(std::make_tuple(
            preceding_info,
            std::string(asn_word.begin(), asn_word.end()),
            SucceedingInfo::SUCCEEDED_BY_WHITESPACE,
            num_preceding_whitespaces,
            asn_word_line_index,
            asn_word_char_index));
        asn_word.clear();
        num_preceding_whitespaces = 1;
        preceding_info = PrecedingInfo::PRECEDED_BY_WHITESPACE;
      }
      // split on all lexical items except dash
      else if (ParseHelper::IsLexicalItem(std::get<0>(c)) &&
               std::get<0>(c) != '-')
      {
        parsed_asn_data.push_back(std::make_tuple(
            preceding_info,
            std::string(asn_word.begin(), asn_word.end()),
            SucceedingInfo::SUCCEEDED_BY_WHITESPACE,
            num_preceding_whitespaces,
            asn_word_line_index,
            asn_word_char_index));
        asn_word.clear();
        num_preceding_whitespaces = 0;
        preceding_info = PrecedingInfo::PRECEDED_BY_WHITESPACE;

        asn_word.push_back(std::get<0>(c));
        asn_word_line_index = std::get<1>(c);
        asn_word_char_index = std::get<2>(c);
      }
      else
      {
        // split on all lexical items except dash
        if (ParseHelper::IsLexicalItem(asn_word.front()) &&
            asn_word.front() != '-')
        {
          parsed_asn_data.push_back(std::make_tuple(
            preceding_info,
            std::string(1, asn_word.front()),
            SucceedingInfo::SUCCEEDED_BY_WHITESPACE,
            num_preceding_whitespaces,
            asn_word_line_index,
            asn_word_char_index));
          asn_word.clear();
          num_preceding_whitespaces = 0;
          preceding_info = PrecedingInfo::PRECEDED_BY_WHITESPACE;

          asn_word.push_back(std::get<0>(c));
          asn_word_line_index = std::get<1>(c);
          asn_word_char_index = std::get<2>(c);
        }
        else
        {
          asn_word.push_back(std::get<0>(c));
        }
      }
    }
  }

  if (!asn_word.empty())
  {
    parsed_asn_data.push_back(std::make_tuple(
          preceding_info,
          std::string(asn_word.begin(), asn_word.end()),
          SucceedingInfo::SUCCEEDED_BY_NEWLINE,
          num_preceding_whitespaces,
          asn_word_line_index,
          asn_word_char_index));
    asn_word.clear();
    num_preceding_whitespaces = 0;
    preceding_info = PrecedingInfo::PRECEDED_BY_NEWLINE;
  }

  SPDLOG_INFO("Parsed file split into {} asn words",
              parsed_asn_data.size());

  for (size_t i = 0; i < parsed_asn_data.size(); i++)
  {
    SPDLOG_DEBUG("[{}:{}] {}{}{}",
        std::get<4>(parsed_asn_data[i]),
        std::get<5>(parsed_asn_data[i]),
        std::get<0>(parsed_asn_data[i]) ==
          PrecedingInfo::PRECEDED_BY_WHITESPACE ?
            "<" + std::to_string(std::get<3>(parsed_asn_data[i])) + " SPC>" :
            "<CR/LF " + std::to_string(std::get<3>(parsed_asn_data[i])) + " SPC>",
        std::get<1>(parsed_asn_data[i]),
        std::get<2>(parsed_asn_data[i]) ==
          SucceedingInfo::SUCCEEDED_BY_WHITESPACE ?
            "<SPC>" : "<CR/LF>");
  }

  size_t asn_data_index = 0;
  std::vector<std::shared_ptr<IProduction>> module_definition_list;

  SPDLOG_INFO("Starting parsing of modules");
  while (asn_data_index < parsed_asn_data.size())
  {
    std::vector<std::string> end_stop;
    std::vector<std::string> parse_path;
    ProductionParseHistory parse_history;

    // Mark the start of parse path so that we do not have empty parse path.
    // This helps ParseLogging to map log to parse path.
    parse_path.push_back("#");

    // Allow ParseLog to work
    auto obj = "ModuleDefinition";
    const auto& asnData = parsed_asn_data;
    auto& asnDataIndex = asn_data_index;
    auto& parsePath = parse_path;
    LOG_START();

    auto prod = ProductionFactory::Get(
        Production::MODULE_DEFINITION);
    if (prod->Parse(
          module_definition_list.size(),
          true,
          asnData,
          asnDataIndex,
          end_stop,
          parsePath,
          parse_history))
    {
      module_definition_list.push_back(prod);
      LOG_PASS();
    }
    else
    {
      LOG_FAIL();
      return std::vector<std::shared_ptr<IProduction>>();
    }
  }

  ParseLog::GetInstance(parsed_asn_data).Dump();

  return module_definition_list;
}
