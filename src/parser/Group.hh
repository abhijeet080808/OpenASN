#pragma once

#include "IProduction.hh"

#include <memory>

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class Group : public IProduction
  {
    public:
      Production GetType() const override;

      bool Parse(const std::vector<Word>& asnData,
                 size_t& asnDataIndex,
                 std::vector<std::string>& endStop,
                 std::vector<std::string>& parsePath) override;

    private:
      std::shared_ptr<IProduction> mNumber;
  };
}
