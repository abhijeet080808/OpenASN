#include "ModuleBody.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

#include "ParseHelper.hh"

using namespace OpenASN;

bool
ModuleBody::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // ModuleBody ::=
  //   Exports Imports AssignmentList
  // | empty

  // Exports

  // Imports

  LOG_START("AssignmentList", asnData);
  AssignmentList assignment_list;
	if (assignment_list.Parse(asnData, endStop))
	{
    mAssignmentList = assignment_list;
    LOG_PASS("AssignmentList", asnData);
  }
  else
  {
    LOG_FAIL("AssignmentList", asnData);
	}

  // Exports Imports AssignmentList all 3 has to be present or none

  return true;
}
