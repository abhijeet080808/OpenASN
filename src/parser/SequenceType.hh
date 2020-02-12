#pragma once

#include "IProduction.hh"

#include <memory>

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class SequenceType : public IProduction
  {
    public:
      Production GetType() const override;

      bool Parse(AsnData& asnData,
                 const std::vector<std::string>& endStop) override;

    public:
      std::shared_ptr<IProduction> mComponentTypeLists;
  };
}
