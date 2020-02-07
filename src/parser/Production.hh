#pragma once

#include "LexicalItem.hh"

#include <string>
#include <vector>

namespace OpenASN
{
  // X.680 08/2015 sec 5.2
  class Production
  {
    public:
      std::string mName;
      std::vector<LexicalItem> mLexicalItems;
  };
}
