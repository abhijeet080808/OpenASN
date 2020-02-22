#include "ModuleBody.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ModuleBody::
GetType() const
{
  return Production::MODULE_BODY;
}

bool
ModuleBody::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // ModuleBody ::=
  //   Exports Imports AssignmentList
  // | empty

  // Exports

  // Imports

  size_t starting_index = asnDataIndex;

  auto obj = "AssignmentList";
  LOG_START();
  auto assignment_list =
    ProductionFactory::Get(Production::ASSIGNMENT_LIST);
	if (assignment_list->Parse(asnData, asnDataIndex, endStop))
	{
    mAssignmentList = assignment_list;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
	}

  // Exports Imports AssignmentList all 3 has to be present or none
}
