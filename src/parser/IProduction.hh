#pragma once

#include "AsnData.hh"

namespace OpenASN
{
  // Represents any one of the productions defined in X.580 08/2015 Annex L
  class IProduction
  {
    public:
      virtual ~IProduction() = default;

      virtual bool Parse(AsnData& asnData,
                         const std::vector<std::string>& endStop) = 0;
  };
}
