#include "EncodingPrefixedType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
EncodingPrefixedType::
GetType() const
{
  return Production::ENCODING_PREFIXED_TYPE;
}

bool
EncodingPrefixedType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // EncodingPrefixedType ::= EncodingPrefix Type

  size_t starting_index = asnDataIndex;

  auto obj = "EncodingPrefix";
  LOG_START();
  auto encoding_prefix =
    ProductionFactory::Get(Production::ENCODING_PREFIX);
  if (encoding_prefix->Parse(asnData, asnDataIndex, endStop))
  {
    mEncodingPrefix = encoding_prefix;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
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
    asnDataIndex = starting_index;
    LOG_FAIL();
    return false;
  }
}
