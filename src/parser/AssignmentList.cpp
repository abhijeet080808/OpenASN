#include "AssignmentList.hh"

#include "CommonDefs.hh"
#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

#include "ParseHelper.hh"

using namespace OpenASN;

bool
AssignmentList::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // AssignmentList ::=
  //   Assignment
  // | AssignmentList Assignment

  while (1)
  {
    LOG_START("Assignment", asnData);
    auto assignment =
      ProductionFactory::Get(Production::ASSIGNMENT);
    if (assignment->Parse(asnData, endStop))
    {
      mAssignment.push_back(assignment);
      LOG_PASS("Assignment", asnData);
    }
    else
    {
      LOG_FAIL("Assignment", asnData);
      break;
    }
  }

  return !mAssignment.empty();
}
