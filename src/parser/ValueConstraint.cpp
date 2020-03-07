#include "ValueConstraint.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ValueConstraint::
GetType() const
{
  return Production::VALUE_CONSTRAINT;
}

bool
ValueConstraint::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ValueConstraint");

  // ValueConstraint ::= Constraint | empty

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
    LOG_FAIL();
    parsePath.pop_back();
    return true;
  }
}
