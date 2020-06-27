#pragma once

#include "Realnumber.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class NegativeRealnumber: public Realnumber
  {
    public:
      Production GetType() const override;

      bool Parse(
          const std::vector<Word>& asnData,
          size_t& asnDataIndex,
          std::vector<std::string>& endStop,
          std::vector<std::string>& parsePath,
          ProductionParseHistory& parseHistory) override;
  };
}
