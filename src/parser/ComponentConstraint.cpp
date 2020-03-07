#include "ComponentConstraint.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ComponentConstraint::
GetType() const
{
  return Production::COMPONENT_CONSTRAINT;
}

bool
ComponentConstraint::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ComponentConstraint");

  // ComponentConstraint ::= ValueConstraint PresenceConstraint

  size_t starting_index = asnDataIndex;

  auto obj = "ValueConstraint";
  LOG_START();
  auto value_constraint =
    ProductionFactory::Get(Production::VALUE_CONSTRAINT);
  if (value_constraint->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mValueConstraint = value_constraint;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "PresenceConstraint";
  LOG_START();
  auto presence_constraint =
    ProductionFactory::Get(Production::PRESENCE_CONSTRAINT);
  if (presence_constraint->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mPresenceConstraint = presence_constraint;
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
