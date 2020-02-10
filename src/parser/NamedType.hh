#pragma once

#include "IProduction.hh"

#include <memory>

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class NamedType : public IProduction
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
      std::shared_ptr<IProduction> mIdentifier;
      std::shared_ptr<IProduction> mType;
  };
}
