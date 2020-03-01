#pragma once

#include <string>
#include <vector>

namespace OpenASN
{
  class StringManip
  {
    public:
      static std::string& Capitalize(std::string& string);

      static std::string Flatten(const std::vector<std::string>& data,
                                 const std::string& separator);
  };
}
