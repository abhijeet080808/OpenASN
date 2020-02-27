#include "ConstraintSpec.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ConstraintSpec::
GetType() const
{
  return Production::CONSTRAINT_SPEC;
}

bool
ConstraintSpec::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // ConstraintSpec ::=
  //   SubtypeConstaint
  // | GeneralConstraint

  size_t starting_index = asnDataIndex;

  auto obj = "SubtypeConstraint";
  LOG_START();
  auto subtype_constraint =
    ProductionFactory::Get(Production::SUBTYPE_CONSTRAINT);
  if (subtype_constraint->Parse(asnData, asnDataIndex, endStop))
  {
    mSubtypeConstraint = subtype_constraint;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

#if 0
  obj = "GeneralConstraint";
  LOG_START();
  auto general_constraint =
    ProductionFactory::Get(Production::GENERAL_CONSTRAINT);
  if (general_constraint->Parse(asnData, asnDataIndex, endStop))
  {
    mGeneralConstraint = general_constraint;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }
#endif
}
