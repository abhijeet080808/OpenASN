#include "InnerTypeConstraints.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
InnerTypeConstraints::
GetType() const
{
  return Production::INNER_TYPE_CONSTRAINTS;
}

bool
InnerTypeConstraints::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("InnerTypeConstraints");

  // InnerTypeConstraints ::=
  //   WITH COMPONENT SingleTypeConstraint
  // | WITH COMPONENTS MultipleTypeConstraints

  size_t starting_index = asnDataIndex;

  auto obj = "WITH";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "COMPONENT";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();

    obj = "SingleTypeConstraint";
    LOG_START();
    auto single_type_constraint =
      ProductionFactory::Get(Production::SINGLE_TYPE_CONSTRAINT);
    if (single_type_constraint->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mSingleTypeConstraint = single_type_constraint;
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
  else
  {
    LOG_FAIL();
  }

  obj = "COMPONENTS";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();

    obj = "MultipleTypeConstraints";
    LOG_START();
    auto multiple_type_constraints =
      ProductionFactory::Get(Production::MULTIPLE_TYPE_CONSTRAINTS);
    if (multiple_type_constraints->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mMultipleTypeConstraints = multiple_type_constraints;
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
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }
}
