#pragma once

#include "IProduction.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class Identifier : public IProduction
  {
    public:
      Production GetType() const override;

      bool Parse(const std::vector<Word>& asnData,
                 size_t& asnDataIndex,
                 std::vector<std::string>& endStop,
                 std::vector<std::string>& parsePath) override;

    public:
      std::string mValue;
  };

  using ValueReference = Identifier;
  // TODO - This is only a subset of the actual non-integerUnicodeLabel
  // Need to add support for exact non-integerUnicodeLabel
  using NonIntegerUnicodeLabel = Identifier;
}
