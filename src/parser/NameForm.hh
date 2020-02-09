#pragma once

#include "AsnData.hh"

#include "Identifier.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class NameForm
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
      Identifier mIdentifier;
  };
}
