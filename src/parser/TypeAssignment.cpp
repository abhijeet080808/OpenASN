#include "TypeAssignment.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
TypeAssignment::
GetType() const
{
  return Production::TYPE_ASSIGNMENT;
}

bool
TypeAssignment::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // TypeAssignment ::=
  // typereference
  // "::="
  // Type

  size_t starting_index = asnDataIndex;

  auto obj = "TypeReference";
  LOG_START();
  auto type_reference =
    ProductionFactory::Get(Production::TYPE_REFERENCE);
  if (type_reference->Parse(asnData, asnDataIndex, endStop))
  {
    mTypeReference = type_reference;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  obj = ":";
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

  obj = ":";
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

  obj = "=";
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
    asnDataIndex = starting_index;
    return false;
  }
}
