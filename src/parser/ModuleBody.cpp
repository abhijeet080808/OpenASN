#include "ModuleBody.hh"

#include "CommonDefs.hh"
#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

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
  auto assignment_list =
    ProductionFactory::Get(Production::ASSIGNMENT_LIST);
	if (assignment_list->Parse(asnData, endStop))
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
