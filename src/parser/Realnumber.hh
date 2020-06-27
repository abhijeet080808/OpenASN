#pragma once

#include "IProduction.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class Realnumber: public IProduction
  {
    public:
      Production GetType() const override;

      bool Parse(
          const std::vector<Word>& asnData,
          size_t& asnDataIndex,
          std::vector<std::string>& endStop,
          std::vector<std::string>& parsePath,
          ProductionParseHistory& parseHistory) override;

    protected:
      int parse(const std::vector<Word>& asnData);

    public:
      std::string mCoeffBeforeDecimal;
      std::string mCoeffAfterDecimal;
      std::string mExponentSign;
      std::string mExponent;
  };
}
