#include "ChoiceType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ChoiceType::
GetType() const
{
  return Production::CHOICE_TYPE;
}

bool
ChoiceType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // ChoiceType ::= CHOICE "{" AlternativeTypeLists "}"

  size_t starting_index = asnDataIndex;

  auto obj = "CHOICE";
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
    return false;
  }

  obj = "{";
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
    return false;
  }

  endStop.push_back("}");

  obj = "AlternativeTypeLists";
  LOG_START();
  auto alternative_type_lists =
    ProductionFactory::Get(Production::ALTERNATIVE_TYPE_LISTS);
  if (alternative_type_lists->Parse(asnData, asnDataIndex, endStop))
  {
    mAlternativeTypeLists = alternative_type_lists;
    endStop.pop_back();
    LOG_PASS();
  }
  else
  {
    endStop.pop_back();
    asnDataIndex = starting_index;
    LOG_FAIL();
    return false;
  }

  obj = "}";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
    return true;
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    return false;
  }
}
