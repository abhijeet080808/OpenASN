#include "Constraint.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Constraint::
GetType() const
{
  return Production::CONSTRAINT;
}

bool
Constraint::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // Constraint ::= "(" ConstraintSpec ExceptionSpec ")"

  size_t starting_index = asnDataIndex;

  auto obj = "(";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  endStop.push_back(")");

  obj = "ConstraintSpec";
  LOG_START();
  auto constraint_spec =
    ProductionFactory::Get(Production::CONSTRAINT_SPEC);
  if (constraint_spec->Parse(asnData, asnDataIndex, endStop))
  {
    mConstraintSpec = constraint_spec;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
    endStop.pop_back();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "ExceptionSpec";
  LOG_START();
  auto exception_spec =
    ProductionFactory::Get(Production::EXCEPTION_SPEC);
  if (exception_spec->Parse(asnData, asnDataIndex, endStop))
  {
    mExceptionSpec = exception_spec;
    LOG_PASS();
    endStop.pop_back();
  }
  else
  {
    LOG_FAIL();
    endStop.pop_back();
    asnDataIndex = starting_index;
    return false;
  }

  obj = ")";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }
}
