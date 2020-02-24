#pragma once

#include "IProduction.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class GeneralizedTime : public IProduction
  {
    public:
      Production GetType() const override;

      bool Parse(const std::vector<Word>& asnData,
                 size_t& asnDataIndex,
                 std::vector<std::string>& endStop) override;

  };
}
