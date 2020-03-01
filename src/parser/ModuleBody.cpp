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
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ModuleBody");

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
	if (assignment_list->Parse(asnData, asnDataIndex, endStop, parsePath))
	{
    mAssignmentList = assignment_list;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
	}

  // Exports Imports AssignmentList all 3 has to be present or none
}
