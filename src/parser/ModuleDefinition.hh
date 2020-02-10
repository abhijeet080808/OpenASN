#pragma once

#include "IProduction.hh"

#include <memory>

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class ModuleDefinition : public IProduction
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
      std::shared_ptr<IProduction> mModuleIdentifier;
      // EncodingReferenceDefault
      // TagDefault
      // ExtensionDefault
      std::shared_ptr<IProduction> mModuleBody;
      // EncodingControlSections
  };
}
