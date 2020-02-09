#pragma once

#include "AsnData.hh"

#include "DefinitiveObjIdComponent.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class DefinitiveObjIdComponentList
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
      std::vector<DefinitiveObjIdComponent> mDefinitiveObjIdComponent;
  };
}
