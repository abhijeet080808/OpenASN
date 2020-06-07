#pragma once

#include "ParseDefs.hh"

#include "parser/ProductionDefs.hh"

#include <cstdint>
#include <vector>

namespace OpenASN
{
  // Represents any one of the productions defined in X.580 08/2015 Annex L
  class IProduction
  {
    public:
      virtual ~IProduction() = default;

      virtual Production GetType() const = 0;

      virtual bool Parse(const std::vector<Word>& asnData,
                         size_t& asnDataIndex,
                         std::vector<std::string>& endStop,
                         std::vector<std::string>& parsePath) = 0;
  };
}
