#include "Parser.hh"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace OpenASN;

void
Parser::
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

    do
    {
      std::string asn_word;
      asn_buf >> asn_word;

      consume(asn_word, state, production);
    }
    while (asn_buf);
  }
}

void
Parser::
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
    }
    else
    {
    }
  }
}
