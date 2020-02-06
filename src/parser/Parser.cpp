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
  }
}
