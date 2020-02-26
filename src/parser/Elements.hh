#pragma once

#include "IProduction.hh"

#include <memory>

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class Elements : public IProduction
  {
    public:
      Production GetType() const override;

      bool Parse(const std::vector<Word>& asnData,
                 size_t& asnDataIndex,
                 std::vector<std::string>& endStop) override;

    public:
      std::shared_ptr<IProduction> mSubtypeElements;
      //std::shared_ptr<IProduction> mObjectSetElements;
      std::shared_ptr<IProduction> mElementSetSpec;
  };
}
