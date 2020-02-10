#pragma once

#include "AsnData.hh"

#include "BuiltinType.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class Type
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
      std::optional<BuiltinType> mBuiltinType;
      // ReferencedType
      // ConstrainedType
  };
}
