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

  auto obj = "SingleValue";
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

  asnDataIndex = starting_index;
  parsePath.pop_back();
  return false;
}
