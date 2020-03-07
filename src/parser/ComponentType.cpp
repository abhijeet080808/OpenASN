#include "ComponentType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ComponentType::
GetType() const
{
  return Production::COMPONENT_TYPE;
}

bool
ComponentType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ComponentType");

  // ComponentType ::=
  //   NamedType
  // | NamedType OPTIONAL
  // | NamedType DEFAULT Value
  // | COMPONENTS OF Type

  size_t starting_index = asnDataIndex;

  auto obj = "NamedType";
  LOG_START();
  auto named_type =
    ProductionFactory::Get(Production::NAMED_TYPE);
  if (named_type->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mNamedType = named_type;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
  }

  if (mNamedType)
  {
    obj = "Optional";
    LOG_START();
    auto optional =
      ProductionFactory::Get(Production::OPTIONAL);
    if (optional->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mOptional = optional;
      LOG_PASS();
      parsePath.pop_back();
      return true;
    }
    else
    {
      LOG_FAIL();

      obj = "DEFAULT";
      LOG_START();
      if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
      {
        ++asnDataIndex;
        LOG_PASS();
      }
      else
      {
        LOG_FAIL();
        parsePath.pop_back();
        return true;
      }

      obj = "Value";
      LOG_START();
      auto value =
        ProductionFactory::Get(Production::VALUE);
      if (value->Parse(asnData, asnDataIndex, endStop, parsePath))
      {
        mValue = value;
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
  }

  obj = "COMPONENTS";
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

  obj = "OF";
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

  obj = "Type";
  LOG_START();
  auto type =
    ProductionFactory::Get(Production::TYPE);
  if (type->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mType = type;
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
