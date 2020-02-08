#pragma once

#include "AsnData.hh"

#include "ModuleDefinitionModuleIdentifier.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class ModuleDefinition
  {
    public:
      bool Parse(AsnData& asnData);

    public:
      ModuleDefinitionModuleIdentifier mModuleIdentifier;
      // EncodingReferenceDefault
      // TagDefault
      // ExtensionDefault
      // ModuleBody
      // EncodingControlSections
  };
}
