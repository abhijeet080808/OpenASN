#include "ConstrainedType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ConstrainedType::
GetType() const
{
  return Production::CONSTRAINED_TYPE;
}

bool
ConstrainedType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // ConstrainedType ::=
  //   Type Constraint
  // | TypeWithConstraint

  size_t starting_index = asnDataIndex;

  auto obj = "Type";
  LOG_START();
  auto type =
    ProductionFactory::Get(Production::TYPE);
  if (type->Parse(asnData, asnDataIndex, endStop))
  {
    mType = type;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
  }

  if (mType)
  {
    obj = "Constraint";
    LOG_START();
    auto constraint =
      ProductionFactory::Get(Production::CONSTRAINT);
    if (constraint->Parse(asnData, asnDataIndex, endStop))
    {
      mConstraint = constraint;
      LOG_PASS();
      return true;
    }
    else
    {
      LOG_FAIL();
      asnDataIndex = starting_index;
      return false;
    }
  }

#if 0
  obj = "TypeWithConstraint";
  LOG_START();
  auto type_with_constraint =
    ProductionFactory::Get(Production::TYPE_WITH_CONSTRAINT);
  if (type_with_constraint->Parse(asnData, asnDataIndex, endStop))
  {
    mTypeWithConstraint = type_with_constraint;
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
  asnDataIndex = starting_index;
  return false;
}
