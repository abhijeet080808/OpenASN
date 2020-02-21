#pragma once

#include "IProduction.hh"

#include <memory>

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class BuiltinType : public IProduction
  {
    public:
      Production GetType() const override;

      bool Parse(AsnData& asnData,
                 const std::vector<std::string>& endStop) override;

    public:
      std::shared_ptr<IProduction> mBitStringType;
      std::shared_ptr<IProduction> mBooleanType;
      std::shared_ptr<IProduction> mChoiceType;
      std::shared_ptr<IProduction> mDateType;
      std::shared_ptr<IProduction> mDateTimeType;
      std::shared_ptr<IProduction> mDurationType;
      std::shared_ptr<IProduction> mEmbeddedPDVType;
      std::shared_ptr<IProduction> mEnumeratedType;
      std::shared_ptr<IProduction> mExternalType;
      std::shared_ptr<IProduction> mIntegerType;
      std::shared_ptr<IProduction> mIRIType;
      std::shared_ptr<IProduction> mNullType;
      std::shared_ptr<IProduction> mObjectIdentifierType;
      std::shared_ptr<IProduction> mOctetStringType;
      std::shared_ptr<IProduction> mRealType;
      std::shared_ptr<IProduction> mSequenceType;
  };
}
