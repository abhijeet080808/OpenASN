#pragma once

#include "IProduction.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class UTF8String : public IProduction
  {
    public:
      Production GetType() const override;

      bool Parse(AsnData& asnData,
                 const std::vector<std::string>& endStop) override;
  };
}