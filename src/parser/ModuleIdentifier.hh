#pragma once

#include "AsnData.hh"

#include "TypeReference.hh"
#include "DefinitiveIdentification.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class ModuleIdentifier
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
      ModuleReference mModuleReference;
      DefinitiveIdentification mDefinitiveIdentification;
  };
}
