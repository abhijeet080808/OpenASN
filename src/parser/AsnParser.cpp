#include "AsnParser.hh"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace OpenASN;

namespace
{
  // X.680 08/2015 sec 12.1.6
  bool IsWhitespace(char c)
  {
    // all newlines are also considered as whitespaces
    return c == 0x09 || // horizontal tab
           c == 0x0a || // line feed
           c == 0x0b || // vertical tab
           c == 0x0c || // form feed
           c == 0x0d || // carriage return
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
  std::cout << "Parsing " << asnFilePath << std::endl;

  std::vector<char> asn_data;
  // list of pair of asn word and indicator of if word is followed by newline
  std::vector<std::tuple<std::string, bool>> parsed_asn_data;

  std::ifstream asn_file(asnFilePath);
  asn_file >> std::noskipws;
  std::copy(std::istream_iterator<char>(asn_file),
            std::istream_iterator<char>(),
            std::back_inserter(asn_data));

  if (asn_data.empty())
  {
    std::cout << "Parsing failed" << std::endl;
  }
  else
  {
    std::vector<char> asn_word;

    for (const auto& c : asn_data)
    {
      if (asn_word.empty())
      {
        if (IsNewline(c))
        {
          continue;
        }
        else if (IsWhitespace(c))
        {
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
          parsed_asn_data.push_back(
              std::make_tuple(std::string(asn_word.begin(), asn_word.end()),
                              true));
          asn_word.clear();
        }
        else if (IsWhitespace(c))
        {
          parsed_asn_data.push_back(
              std::make_tuple(std::string(asn_word.begin(), asn_word.end()),
                              false));
          asn_word.clear();
        }
        else
        {
          asn_word.push_back(c);
        }
      }
    }

    if (!asn_word.empty())
    {
      parsed_asn_data.push_back(
          std::make_tuple(std::string(asn_word.begin(), asn_word.end()), true));
      asn_word.clear();
    }

    for (const auto& asn_word : parsed_asn_data)
    {
      std::cout << std::get<0>(asn_word) << " " << std::get<1>(asn_word) << std::endl;
    }

    ParserState state = ParserState::START;
    Production production;


    //consume(asn_word.str(), state, production);

  }
}

void
AsnParser::
consume(const std::string& asnWord,
        ParserState& state,
        Production& production)
{
  std::cout << asnWord << std::endl;

  if (state == START)
  {
    production.mName = asnWord;
    state = READ_PRODUCTION_NAME;
    return;
  }

  if (state == READ_PRODUCTION_NAME)
  {
    if (asnWord == ":=")
    {
      return;
    }
    else
    {
      return;
    }
  }
}
