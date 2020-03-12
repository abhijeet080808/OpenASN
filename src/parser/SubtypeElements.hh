#pragma once

#include "IProduction.hh"

#include <memory>

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class SubtypeElements : public IProduction
  {
    public:
      Production GetType() const override;

      bool Parse(const std::vector<Word>& asnData,
                 size_t& asnDataIndex,
                 std::vector<std::string>& endStop,
                 std::vector<std::string>& parsePath) override;

    public:
      std::shared_ptr<IProduction> mContainedSubtype;
      std::shared_ptr<IProduction> mValueRange;
      std::shared_ptr<IProduction> mSingleValue;
      std::shared_ptr<IProduction> mSizeConstraint;
      std::shared_ptr<IProduction> mPermittedAlphabet;
      std::shared_ptr<IProduction> mTypeConstraint;
      std::shared_ptr<IProduction> mInnerTypeConstraints;
      std::shared_ptr<IProduction> mPatternConstraint;
      std::shared_ptr<IProduction> mPropertySettings;
  };
}
