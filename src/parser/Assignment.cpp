#include "Assignment.hh"

#include "CommonDefs.hh"
#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

#include "ParseHelper.hh"

using namespace OpenASN;

bool
Assignment::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // Assignment ::=
  //   TypeAssignment
  // | ValueAssignment
  // | XMLValueAssignment
  // | ValueSetTypeAssignment
  // | ObjectClassAssignment
  // | ObjectAssignment
  // | ObjectSetAssignment
  // | ParameterizedAssignment

  LOG_START("TypeAssignment", asnData);
  auto type_assignment =
    ProductionFactory::Get(Production::TYPE_ASSIGNMENT);
  if (type_assignment->Parse(asnData, endStop))
  {
    mTypeAssignment = type_assignment;
    LOG_PASS("TypeAssignment", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("AssignmentList", asnData);
  }

  return false;
}
