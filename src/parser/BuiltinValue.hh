#pragma once

#include "IProduction.hh"

#include <memory>

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class BuiltinValue : public IProduction
  {
    public:
      Production GetType() const override;

      bool Parse(const std::vector<Word>& asnData,
                 size_t& asnDataIndex,
                 std::vector<std::string>& endStop,
                 std::vector<std::string>& parsePath) override;

    public:
      std::shared_ptr<IProduction> mBitStringValue;
      std::shared_ptr<IProduction> mBooleanValue;
      std::shared_ptr<IProduction> mCharacterStringValue;
      std::shared_ptr<IProduction> mChoiceValue;
      // std::shared_ptr<IProduction> mEnumeratedValue;
      // std::shared_ptr<IProduction> mExternalValue;
      // std::shared_ptr<IProduction> mInstanceOfValue;
      std::shared_ptr<IProduction> mIntegerValue;
      // std::shared_ptr<IProduction> mIRIValue;
      // std::shared_ptr<IProduction> mNullValue;
      // std::shared_ptr<IProduction> mObjectIdentifierValue;
      // std::shared_ptr<IProduction> mOctetStringValue;
      // std::shared_ptr<IProduction> mPrefixedValue;
      // std::shared_ptr<IProduction> mRealValue;
      // std::shared_ptr<IProduction> mRelativeIRIValue;
      // std::shared_ptr<IProduction> mRelativeOIDValue;
      // std::shared_ptr<IProduction> mSequenceValue;
      // std::shared_ptr<IProduction> mSequenceOfValue;
      // std::shared_ptr<IProduction> mSetValue;
      // std::shared_ptr<IProduction> mSetOfValue;
      // std::shared_ptr<IProduction> mTimeValue;
  };
}
