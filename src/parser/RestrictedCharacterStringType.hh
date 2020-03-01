#pragma once

#include "IProduction.hh"

#include <memory>

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class RestrictedCharacterStringType : public IProduction
  {
    public:
      Production GetType() const override;

      bool Parse(const std::vector<Word>& asnData,
                 size_t& asnDataIndex,
                 std::vector<std::string>& endStop,
                 std::vector<std::string>& parsePath) override;

    private:
      std::shared_ptr<IProduction> mBMPString;
      std::shared_ptr<IProduction> mGeneralString;
      std::shared_ptr<IProduction> mGraphicString;
      std::shared_ptr<IProduction> mIA5String;
      std::shared_ptr<IProduction> mISO646String;
      std::shared_ptr<IProduction> mNumericString;
      std::shared_ptr<IProduction> mPrintableString;
      std::shared_ptr<IProduction> mT61String;
      std::shared_ptr<IProduction> mTeletexString;
      std::shared_ptr<IProduction> mUniversalString;
      std::shared_ptr<IProduction> mUTF8String;
      std::shared_ptr<IProduction> mVideotexString;
      std::shared_ptr<IProduction> mVisibleString;
  };
}
