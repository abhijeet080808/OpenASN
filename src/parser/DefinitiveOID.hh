#pragma once

#include "AsnData.hh"

#include "DefinitiveObjIdComponentList.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class DefinitiveOID
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
      DefinitiveObjIdComponentList mDefinitiveObjIdComponentList;
  };
}
