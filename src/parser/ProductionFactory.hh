#pragma once

#include "IProduction.hh"

#include "common/CommonDefs.hh"

#include <memory>

namespace OpenASN
{
  class ProductionFactory
  {
    public:
      static std::shared_ptr<IProduction> Get(Production production);
  };
}
