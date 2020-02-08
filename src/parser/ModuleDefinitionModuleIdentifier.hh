#pragma once

#include "AsnData.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class ModuleDefinitionModuleIdentifier
  {
    public:
      bool Parse(AsnData& asnData);

    public:
      std::string mModuleReference;
      // DefinitiveIdentification
  };
}
