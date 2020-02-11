#pragma once

#include "IProduction.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class BooleanType : public IProduction
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);
  };
}