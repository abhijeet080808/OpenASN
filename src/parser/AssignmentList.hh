#pragma once

#include "AsnData.hh"

#include "Assignment.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class AssignmentList
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
      std::vector<Assignment> mAssignment;
  };
}
