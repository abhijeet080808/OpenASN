#pragma once

#include "IProduction.hh"

#include <memory>

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class DefinitiveObjIdComponentList : public IProduction
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
      std::vector<std::shared_ptr<IProduction>> mDefinitiveObjIdComponent;
  };
}
