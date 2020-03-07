#include "SingleTypeConstraint.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
SingleTypeConstraint::
GetType() const
{
  return Production::SINGLE_TYPE_CONSTRAINT;
}

bool
SingleTypeConstraint::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("SingleTypeConstraint");

  // SingleTypeConstraint ::= Constraint

  size_t starting_index = asnDataIndex;

  auto obj = "Constraint";
  LOG_START();
  auto constraint =
    ProductionFactory::Get(Production::CONSTRAINT);
  if (constraint->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mConstraint = constraint;
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
}
