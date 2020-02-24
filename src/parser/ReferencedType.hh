#pragma once

#include "IProduction.hh"

#include <memory>

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class ReferencedType : public IProduction
  {
    public:
      Production GetType() const override;

      bool Parse(const std::vector<Word>& asnData,
                 size_t& asnDataIndex,
                 std::vector<std::string>& endStop) override;

    public:
      std::shared_ptr<IProduction> mDefinedType;
      //std::shared_ptr<IProduction> mUsefulType;
      //std::shared_ptr<IProduction> mSelectionType;
      //std::shared_ptr<IProduction> mTypeFromObject;
      //std::shared_ptr<IProduction> mValueSetFromObjects;
  };
}
