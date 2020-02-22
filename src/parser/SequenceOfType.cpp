#include "SequenceOfType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
SequenceOfType::
GetType() const
{
  return Production::SEQUENCE_OF_TYPE;
}

bool
SequenceOfType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // SequenceOfType ::= SEQUENCE OF Type | SEQUENCE OF NamedType

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
