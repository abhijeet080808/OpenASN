#include "StringManip.hh"

#include <cctype>
#include <sstream>

using namespace OpenASN;

std::string&
StringManip::
Capitalize(std::string& string)
{
  string[0] = std::toupper(string[0]);
  return string;
}

std::string
StringManip::
Flatten(const std::vector<std::string>& data,
        const std::string& separator)
{
  std::stringstream data_ss;
  for (size_t i = 0; i < data.size(); i++)
  {
    data_ss << data.at(i);

    if (i != data.size() - 1)
    {
      data_ss << separator;
    }
  }

  return data_ss.str();
}
