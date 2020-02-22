#include "SetOfType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
SetOfType::
GetType() const
{
  return Production::SET_OF_TYPE;
}

bool
SetOfType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // SetOfType ::= SET OF Type | SET OF NamedType

  size_t starting_index = asnDataIndex;

  auto obj = "SET";
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

  obj = "OF";
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

  obj = "Type";
  LOG_START();
  auto type =
    ProductionFactory::Get(Production::TYPE);
  if (type->Parse(asnData, asnDataIndex, endStop))
  {
    mType = type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "NamedType";
  LOG_START();
  auto named_type =
    ProductionFactory::Get(Production::NAMED_TYPE);
  if (named_type->Parse(asnData, asnDataIndex, endStop))
  {
    mNamedType = named_type;
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
