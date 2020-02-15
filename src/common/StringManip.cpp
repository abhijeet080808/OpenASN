#include "StringManip.hh"

#include <cctype>

using namespace OpenASN;


std::string&
StringManip::
Capitalize(std::string& string)
{
  string[0] = std::toupper(string[0]);
  return string;
}
