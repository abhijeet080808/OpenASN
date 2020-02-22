#include "SequenceType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
SequenceType::
GetType() const
{
  return Production::SEQUENCE_TYPE;
}

bool
SequenceType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // SequenceType ::=
  //   SEQUENCE "{" "}"
  // | SEQUENCE "{" ExtensionAndException OptionalExtensionMarker "}"
  // | SEQUENCE "{" ComponentTypeLists "}"

  size_t starting_index = asnDataIndex;

  auto obj = "SEQUENCE";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "{";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "}";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  endStop.push_back("}");

  obj = "ComponentTypeLists";
  LOG_START();
  auto component_type_lists =
    ProductionFactory::Get(Production::COMPONENT_TYPE_LISTS);
  if (component_type_lists->Parse(asnData, asnDataIndex, endStop))
  {
    mComponentTypeLists = component_type_lists;
    LOG_PASS();
    endStop.pop_back();
  }
  else
  {
    LOG_FAIL();
    endStop.pop_back();
    asnDataIndex = starting_index;
    return false;
  }

  // ExtensionAndException OptionalExtensionMarker

  obj = "}";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }
}
