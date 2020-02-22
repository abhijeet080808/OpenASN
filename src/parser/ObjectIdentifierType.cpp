#include "ObjectIdentifierType.hh"

#include "ParseHelper.hh"
#include "LoggingMacros.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ObjectIdentifierType::
GetType() const
{
  return Production::OBJECT_IDENTIFIER_TYPE;
}

bool
ObjectIdentifierType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>&)
{
  // ObjectIdentifierType ::= OBJECT IDENTIFIER

  size_t starting_index = asnDataIndex;

  auto obj = "OBJECT";
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

  obj = "IDENTIFIER";
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
