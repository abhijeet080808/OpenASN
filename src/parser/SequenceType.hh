#pragma once

#include "AsnData.hh"

#include "ComponentTypeLists.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class SequenceType
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
      std::optional<ComponentTypeLists> mComponentTypeLists;
  };
}
