#pragma once

#include <string>

namespace OpenASN
{
  // X.680 08/2015 sec 12
  class LexicalItem
  {
    public:
      std::string mName;
      std::string mType;
  };
}
