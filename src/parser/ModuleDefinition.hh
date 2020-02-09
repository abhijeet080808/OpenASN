#pragma once

#include "AsnData.hh"
#include "CommonDefs.hh"

#include "ModuleIdentifier.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class ModuleDefinition
  {
    public:
      ParseResult Parse(AsnData& asnData,
                        const std::vector<std::string>& endStop);

    public:
      ModuleIdentifier mModuleIdentifier;
      // EncodingReferenceDefault
      // TagDefault
      // ExtensionDefault
      // ModuleBody
      // EncodingControlSections
  };
}
