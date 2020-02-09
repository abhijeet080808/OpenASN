#pragma once

#include <string>
#include <vector>

namespace OpenASN
{
  class ParseHelper
  {
    public:
      static bool HitEndStop(const std::string& asnWord,
                             const std::vector<std::string>& endStop);

      static bool IsReserved(const std::string& asnWord);
  };
}
