#pragma once

#include "IProduction.hh"

#include <memory>

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class ExceptionIdentification : public IProduction
  {
    public:
      Production GetType() const override;

      bool Parse(const std::vector<Word>& asnData,
                 size_t& asnDataIndex,
                 std::vector<std::string>& endStop) override;

    public:
      std::shared_ptr<IProduction> mSignedNumber;
      std::shared_ptr<IProduction> mDefinedValue;
      std::shared_ptr<IProduction> mType;
      std::shared_ptr<IProduction> mValue;
  };
}
