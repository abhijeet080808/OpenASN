#include "PresenceConstraint.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
PresenceConstraint::
GetType() const
{
  return Production::PRESENCE_CONSTRAINT;
}

bool
PresenceConstraint::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("PresenceConstraint");

  // PresenceConstraint ::= PRESENT | ABSENT | OPTIONAL | empty

  auto obj = "Present";
  LOG_START();
  auto present =
    ProductionFactory::Get(Production::PRESENT);
  if (present->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mPresent = present;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "Absent";
  LOG_START();
  auto absent =
    ProductionFactory::Get(Production::ABSENT);
  if (absent->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mAbsent = absent;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "Optional";
  LOG_START();
  auto optional =
    ProductionFactory::Get(Production::OPTIONAL);
  if (optional->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mOptional = optional;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  parsePath.pop_back();
  return true;
}
