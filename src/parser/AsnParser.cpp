#include "AsnParser.hh"

#include "AsnData.hh"
#include "ModuleDefinition.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

#include <fstream>
#include <iterator>
#include <sstream>

using namespace OpenASN;

namespace
{
  // X.680 08/2015 sec 12.1.6
  bool IsWhitespace(char c)
  {
    return c == 0x09 || // horizontal tab
           c == 0x20;   // space
  }

  // X.680 08/2015 sec 12.1.6
  bool IsNewline(char c)
  {
    return c == 0x0a || // line feed
           c == 0x0b || // vertical tab
           c == 0x0c || // form feed
           c == 0x0d;   // carriage return
  }
}

void
AsnParser::
Parse(const std::string& asnFilePath)
{
  SPDLOG_INFO("Parsing {}",
              asnFilePath);

  std::vector<char> asn_file_data;
  AsnData parsed_asn_data;

  std::ifstream asn_file(asnFilePath);
  asn_file >> std::noskipws;
  std::copy(std::istream_iterator<char>(asn_file),
            std::istream_iterator<char>(),
            std::back_inserter(asn_file_data));

  if (asn_file_data.empty())
  {
    SPDLOG_ERROR("Parsing of empty file {} failed",
                 asnFilePath);
  }
  else
  {
    std::vector<char> asn_word;

    AsnData::PrecedingInfo preceding_info =
      AsnData::PrecedingInfo::PRECEDED_BY_NEWLINE;

    for (const auto& c : asn_file_data)
    {
      if (asn_word.empty())
      {
        if (IsNewline(c))
        {
          preceding_info = AsnData::PrecedingInfo::PRECEDED_BY_NEWLINE;
          continue;
        }
        else if (IsWhitespace(c))
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
        if (IsNewline(c))
        {
          parsed_asn_data.Insert(
              preceding_info,
              std::string(asn_word.begin(), asn_word.end()),
              AsnData::SucceedingInfo::SUCCEEDED_BY_NEWLINE);
          asn_word.clear();
          preceding_info = AsnData::PrecedingInfo::PRECEDED_BY_NEWLINE;
        }
        else if (IsWhitespace(c))
        {
          parsed_asn_data.Insert(
              preceding_info,
              std::string(asn_word.begin(), asn_word.end()),
              AsnData::SucceedingInfo::SUCCEEDED_BY_WHITESPACE);
          asn_word.clear();
          preceding_info = AsnData::PrecedingInfo::PRECEDED_BY_WHITESPACE;
        }
        else
        {
          asn_word.push_back(c);
        }
      }
    }

    if (!asn_word.empty())
    {
      parsed_asn_data.Insert(preceding_info,
                             std::string(asn_word.begin(), asn_word.end()),
                             AsnData::SucceedingInfo::SUCCEEDED_BY_NEWLINE);
      asn_word.clear();
      preceding_info = AsnData::PrecedingInfo::PRECEDED_BY_NEWLINE;
    }

    SPDLOG_INFO("Parsed file split into {} asn words",
                parsed_asn_data.GetSize());

    auto parsed_asn_word = parsed_asn_data.PeekCurrent();
    while (parsed_asn_word.has_value())
    {
      SPDLOG_DEBUG("{}{}{}",
          std::get<0>(parsed_asn_word.value()) ==
            AsnData::PrecedingInfo::PRECEDED_BY_WHITESPACE ?
              "<SPC>" : "<CR/LF>",
          std::get<1>(parsed_asn_word.value()),
          std::get<2>(parsed_asn_word.value()) ==
            AsnData::SucceedingInfo::SUCCEEDED_BY_WHITESPACE ?
              "<SPC>" : "<CR/LF>");

      parsed_asn_data.IncrementCurrentIndex();
      parsed_asn_word = parsed_asn_data.PeekCurrent();
    }

    parsed_asn_data.ResetCurrentIndex();

    ModuleDefinition module_definition;
    LOG_START("ModuleDefinition", parsed_asn_data);
    bool ret = module_definition.Parse(parsed_asn_data,
                                       std::vector<std::string>{ "END" });

    if (ret)
    {
      LOG_PASS("ModuleDefinition", parsed_asn_data);
    }
    else
    {
      LOG_FAIL("ModuleDefinition", parsed_asn_data);
    }
  }
}