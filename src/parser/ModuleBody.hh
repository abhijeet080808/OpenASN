#pragma once

#include "AsnData.hh"

#include "AssignmentList.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class ModuleBody
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
      std::optional<AssignmentList> mAssignmentList;
  };
}
