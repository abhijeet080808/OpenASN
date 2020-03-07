#include "SubtypeElements.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
SubtypeElements::
GetType() const
{
  return Production::SUBTYPE_ELEMENTS;
}

bool
SubtypeElements::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("SubtypeElements");

  // SubtypeElements ::=
  //   SingleValue
  // | ContainedSubtype
  // | ValueRange
  // | PermittedAlphabet
  // | SizeConstraint
  // | TypeConstraint
  // | InnerTypeConstraints
  // | PatternConstraint
  // | PropertySettings
  // | DurationRange
  // | TimePointRange
  // | RecurrenceRange

  size_t starting_index = asnDataIndex;

  auto obj = "ContainedSubtype";
  LOG_START();
  auto contained_subtype =
    ProductionFactory::Get(Production::CONTAINED_SUBTYPE);
  if (contained_subtype->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mContainedSubtype = contained_subtype;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  // This is added before SingleValue to prevent SingleValue from wrongly
  // consuming values meant for this type
  obj = "ValueRange";
  LOG_START();
  auto value_range =
    ProductionFactory::Get(Production::VALUE_RANGE);
  if (value_range->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mValueRange = value_range;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "SingleValue";
  LOG_START();
  auto single_value =
    ProductionFactory::Get(Production::SINGLE_VALUE);
  if (single_value->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mSingleValue = single_value;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "SizeConstraint";
  LOG_START();
  auto size_constraint =
    ProductionFactory::Get(Production::SIZE_CONSTRAINT);
  if (size_constraint->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mSizeConstraint = size_constraint;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "PermittedAlphabet";
  LOG_START();
  auto permitted_alphabet =
    ProductionFactory::Get(Production::PERMITTED_ALPHABET);
  if (permitted_alphabet->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mPermittedAlphabet = permitted_alphabet;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  /* XXX Gets consumed via ContainedSubtype
  obj = "TypeConstraint";
  LOG_START();
  auto type_constraint =
    ProductionFactory::Get(Production::TYPE_CONSTRAINT);
  if (type_constraint->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mTypeConstraint = type_constraint;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }
  */

  obj = "InnerTypeConstraints";
  LOG_START();
  auto inner_type_constraints =
    ProductionFactory::Get(Production::INNER_TYPE_CONSTRAINTS);
  if (inner_type_constraints->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mInnerTypeConstraints = inner_type_constraints;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  asnDataIndex = starting_index;
  parsePath.pop_back();
  return false;
}
