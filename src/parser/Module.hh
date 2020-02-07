#pragma once

#include "Production.hh"

#include <string>
#include <vector>

namespace OpenASN
{
  // X.680 08/2015 sec 13.1
  class Module
  {
    public:
      std::vector<Production> mProductions;
  };
}
