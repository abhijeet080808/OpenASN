#pragma once

#include "CommonDefs.hh"
#include "IProduction.hh"

namespace OpenASN
{
  class ProductionFactory
  {
    public:
      static std::shared_ptr<IProduction> Get(Production production);
  };
}
