#pragma once

#include "AsnData.hh"

#include "BooleanType.hh"
#include "SequenceType.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class BuiltinType
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
      std::optional<BooleanType> mBooleanType;
      std::optional<SequenceType> mSequenceType;
  };
}
