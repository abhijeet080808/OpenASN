#include "AsnParser.hh"

#include "LoggingMacros.hh"
#include "ModuleDefinition.hh"
#include "ParseDefs.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "common/CommonDefs.hh"
#include "spdlog/spdlog.h"

#include <fstream>
#include <iterator>
#include <sstream>

using namespace OpenASN;

std::shared_ptr<IProduction>
AsnParser::
Parse(const std::string& asnFilePath)
{
  SPDLOG_INFO("Parsing \"{}\"",
              asnFilePath);

  std::vector<char> asn_file_data;
  std::vector<Word> parsed_asn_data;

  std::ifstream asn_file(asnFilePath);
  asn_file >> std::noskipws;
  std::copy(std::istream_iterator<char>(asn_file),
            std::istream_iterator<char>(),
            std::back_inserter(asn_file_data));

  if (asn_file_data.empty())
  {
    SPDLOG_ERROR("Parsing of empty file \"{}\" failed",
                 asnFilePath);
    return nullptr;
  }

  // remove all comments of type -- xx -- and /* xx */
  int num_single_line_comment_started = 0;
  int num_multi_line_comment_started = 0;
  for (size_t i = 0; i < asn_file_data.size(); i++)
  {
    if (num_single_line_comment_started)
    {
      if ((i + 1) < asn_file_data.size() &&
          asn_file_data.at(i) == '-' &&
          asn_file_data.at(i + 1) == '-')
      {
        num_single_line_comment_started = 0;
        asn_file_data.erase(asn_file_data.begin() + i);
        asn_file_data.erase(asn_file_data.begin() + i);
        --i;
      }
      else if (asn_file_data.at(i) == '\n')
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
          asn_file_data.at(i) == '/' &&
          asn_file_data.at(i + 1) == '*')
      {
        ++num_multi_line_comment_started;
        asn_file_data.erase(asn_file_data.begin() + i);
        asn_file_data.erase(asn_file_data.begin() + i);
        --i;
      }
      else if ((i + 1) < asn_file_data.size() &&
               asn_file_data.at(i) == '*' &&
               asn_file_data.at(i + 1) == '/')
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
          asn_file_data.at(i) == '-' &&
          asn_file_data.at(i + 1) == '-')
      {
        num_single_line_comment_started = 1;
        asn_file_data.erase(asn_file_data.begin() + i);
        asn_file_data.erase(asn_file_data.begin() + i);
        --i;
      }
      else if ((i + 1) < asn_file_data.size() &&
               asn_file_data.at(i) == '/' &&
               asn_file_data.at(i + 1) == '*')
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
    asn_file_data_ss << asn_file_data.at(i);
  }
  SPDLOG_INFO("{}", asn_file_data_ss.str());

  std::vector<char> asn_word;

  PrecedingInfo preceding_info =
    PrecedingInfo::PRECEDED_BY_NEWLINE;

  for (const auto& c : asn_file_data)
  {
    if (asn_word.empty())
    {
      if (ParseHelper::IsNewline(c))
      {
        preceding_info = PrecedingInfo::PRECEDED_BY_NEWLINE;
        continue;
      }
      else if (ParseHelper::IsWhitespace(c))
      {
        // newline has priority until the first word is reached
        // for the current line, so if it is PRECEDED_BY_NEWLINE,
        // let it remain so
        //
        // if it is already PRECEDED_BY_WHITESPACE, nothing to change
        continue;
      }
      else
      {
        asn_word.push_back(c);
      }
    }
    else
    {
      if (ParseHelper::IsNewline(c))
      {
        parsed_asn_data.push_back(std::make_tuple(
            preceding_info,
            std::string(asn_word.begin(), asn_word.end()),
            SucceedingInfo::SUCCEEDED_BY_NEWLINE));
        asn_word.clear();
        preceding_info = PrecedingInfo::PRECEDED_BY_NEWLINE;
      }
      else if (ParseHelper::IsWhitespace(c))
      {
        parsed_asn_data.push_back(std::make_tuple(
            preceding_info,
            std::string(asn_word.begin(), asn_word.end()),
            SucceedingInfo::SUCCEEDED_BY_WHITESPACE));
        asn_word.clear();
        preceding_info = PrecedingInfo::PRECEDED_BY_WHITESPACE;
      }
      // split on all lexical items except dash
      else if (ParseHelper::IsLexicalItem(c) && c != '-')
      {
        parsed_asn_data.push_back(std::make_tuple(
            preceding_info,
            std::string(asn_word.begin(), asn_word.end()),
            SucceedingInfo::SUCCEEDED_BY_WHITESPACE));
        asn_word.clear();
        preceding_info = PrecedingInfo::PRECEDED_BY_WHITESPACE;

        asn_word.push_back(c);
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
            SucceedingInfo::SUCCEEDED_BY_WHITESPACE));
          asn_word.clear();
          preceding_info = PrecedingInfo::PRECEDED_BY_WHITESPACE;

          asn_word.push_back(c);
        }
        else
        {
          asn_word.push_back(c);
        }
      }
    }
  }

  if (!asn_word.empty())
  {
    parsed_asn_data.push_back(std::make_tuple(
          preceding_info,
          std::string(asn_word.begin(), asn_word.end()),
          SucceedingInfo::SUCCEEDED_BY_NEWLINE));
    asn_word.clear();
    preceding_info = PrecedingInfo::PRECEDED_BY_NEWLINE;
  }

  SPDLOG_INFO("Parsed file split into {} asn words",
              parsed_asn_data.size());

  for (const auto& parsed_asn_word : parsed_asn_data)
  {
    SPDLOG_DEBUG("{}{}{}",
        std::get<0>(parsed_asn_word) ==
          PrecedingInfo::PRECEDED_BY_WHITESPACE ?
            "<SPC>" : "<CR/LF>",
        std::get<1>(parsed_asn_word),
        std::get<2>(parsed_asn_word) ==
          SucceedingInfo::SUCCEEDED_BY_WHITESPACE ?
            "<SPC>" : "<CR/LF>");
  }

  size_t asn_data_index = 0;
  std::vector<std::string> end_stop;
  LOG_START_GEN("ModuleDefinition", parsed_asn_data, asn_data_index);
  auto module_definition =
    ProductionFactory::Get(Production::MODULE_DEFINITION);
  if (module_definition->Parse(parsed_asn_data,
                               asn_data_index,
                               end_stop))
  {
    LOG_PASS_GEN("ModuleDefinition", parsed_asn_data, asn_data_index);
    return module_definition;
  }
  else
  {
    LOG_FAIL_GEN("ModuleDefinition", parsed_asn_data, asn_data_index);
    return nullptr;
  }
}
