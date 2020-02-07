#include "AsnParser.hh"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace OpenASN;

void
AsnParser::
Parse(const std::string& asnFilePath)
{
  std::cout << "Parsing " << asnFilePath << std::endl;

  std::ifstream asn_file(asnFilePath);
  std::stringstream asn_buf;
  asn_buf << asn_file.rdbuf();

  // XXX dont use this
  if (asn_buf.str().empty())
  {
    std::cout << "Parsing failed" << std::endl;
  }
  else
  {
    std::cout << asn_buf.str() << std::endl;

    ParserState state = ParserState::START;
    Production production;

    while (1)
    {
      std::stringstream asn_word;
      char c;
      while (asn_buf.get(c))
      {
        if (c == ' ')
        {
          break;
        }
        else if (c == '\n')
        {
          break;
        }
        else
        {
          asn_word << c;
        }
      }

      consume(asn_word.str(), state, production);

    }
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
