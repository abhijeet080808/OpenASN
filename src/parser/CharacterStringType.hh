#pragma once

#include "IProduction.hh"

#include <memory>

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class CharacterStringType : public IProduction
  {
    public:
      Production GetType() const override;

      bool Parse(AsnData& asnData,
                 const std::vector<std::string>& endStop) override;

    private:
      std::shared_ptr<IProduction> mRestrictedCharacterStringType;
      std::shared_ptr<IProduction> mUnrestrictedCharacterStringType;
  };
}
