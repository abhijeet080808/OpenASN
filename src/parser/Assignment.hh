#pragma once

#include "AsnData.hh"

#include "TypeAssignment.hh"

namespace OpenASN
{
  // X.680 08/2015 Annex L
  class Assignment
  {
    public:
      bool Parse(AsnData& asnData, const std::vector<std::string>& endStop);

    public:
      std::optional<TypeAssignment> mTypeAssignment;
      // ValueAssignment
      // XMLValueAssignment
      // ValueSetTypeAssignment
      // ObjectClassAssignment
      // ObjectAssignment
      // ObjectSetAssignment
      // ParameterizedAssignment
  };
}
