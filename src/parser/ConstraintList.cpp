#include "ConstraintList.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ConstraintList::
GetType() const
{
  return Production::CONSTRAINT_LIST;
}

bool
ConstraintList::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ConstraintList");

  // (See Type)
  // ConstraintList ::=
  //   Constraint
  // | ConstraintList Constraint

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "Constraint";
    LOG_START();
    auto constraint =
      ProductionFactory::Get(Production::CONSTRAINT);
    if (constraint->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mConstraint.push_back(constraint);
      LOG_PASS();
    }
    else
    {
      LOG_FAIL();
      break;
    }
  }

  if (mConstraint.empty())
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
