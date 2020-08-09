#pragma once

#include "Number.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class NegativeNumber: public Number
  {
    public:
      Production GetType() const override;

      bool Parse(
          size_t productionIndex,
          bool prodIndexPresent,
          const std::vector<Word>& asnData,
          size_t& asnDataIndex,
          std::vector<std::string>& endStop,
          std::vector<std::string>& parsePath,
          ProductionParseHistory& parseHistory) override;
  };
}
