#include "IntegerType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
IntegerType::
GetType() const
{
  return Production::INTEGER_TYPE;
}

bool
IntegerType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // IntegerType ::=
  //   INTEGER
  // | INTEGER "{" NamedNumberList "}"

  size_t starting_index = asnDataIndex;

  auto obj = "INTEGER";
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
    LOG_FAIL();
    return true;
  }

  endStop.push_back("}");

  obj = "NamedNumberList";
  LOG_START();
  auto named_number_list =
    ProductionFactory::Get(Production::NAMED_NUMBER_LIST);
  if (named_number_list->Parse(asnData, asnDataIndex, endStop))
  {
    mNamedNumberList = named_number_list;
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
