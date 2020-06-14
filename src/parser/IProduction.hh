#pragma once

#include "ParseDefs.hh"

#include "parser/ProductionDefs.hh"

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

namespace OpenASN
{
  // Represents any one of the productions defined in X.580 08/2015 Annex L
  class IProduction
  {
    public:
      virtual ~IProduction() = default;

      virtual Production GetType() const = 0;

      virtual bool Parse(
          const std::vector<Word>& asnData,
          size_t& asnDataIndex,
          std::vector<std::string>& endStop,
          std::vector<std::string>& parsePath,
          std::map<std::pair<size_t, Production>,
                   std::pair<std::shared_ptr<IProduction>, size_t>>& parseHistory) = 0;
  };

  // Each ASN file is split into multiple Word as defined above, with the first
  // Word having index of 0 and so on.
  //
  // Key is Word index and the Production type that was parsed at that index.
  //
  // Value is the Production that was parsed along with the position of the next
  // Word index after parse of the production has completed and consumed 1 or
  // more Word.
  using ProductionParseHistory =
    std::map<std::pair<size_t, Production>,
                       std::pair<std::shared_ptr<IProduction>, size_t>>;
}
