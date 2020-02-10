#pragma once

#include "AsnData.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class BooleanType
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);
  };
}
