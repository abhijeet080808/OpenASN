#include "AssignmentList.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
AssignmentList::
GetType() const
{
  return Production::ASSIGNMENT_LIST;
}

bool
AssignmentList::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("AssignmentList");

  // AssignmentList ::=
  //   Assignment
  // | AssignmentList Assignment

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "Assignment";
    LOG_START();
    auto assignment =
      ProductionFactory::Get(Production::ASSIGNMENT);
    if (assignment->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mAssignment.push_back(assignment);
      LOG_PASS();
    }
    else
    {
      LOG_FAIL();
      break;
    }
  }

  if (mAssignment.empty())
  {
    asnDataIndex = starting_index;
    parsePath.pop_back();
    return false;
  }
  else
  {
    parsePath.pop_back();
    return true;
  }
}
