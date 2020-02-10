#pragma once

#include "AsnData.hh"

#include "TypeReference.hh"
#include "Type.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class TypeAssignment
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
      TypeReference mTypeReference;
      Type mType;
  };
}
