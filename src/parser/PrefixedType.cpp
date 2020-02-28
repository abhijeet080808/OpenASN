#include "PrefixedType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
PrefixedType::
GetType() const
{
  return Production::PREFIXED_TYPE;
}

bool
PrefixedType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // PrefixedType ::=
  //   TaggedType
  // | EncodingPrefixedType

  size_t starting_index = asnDataIndex;

  auto obj = "TaggedType";
  LOG_START();
  auto tagged_type =
    ProductionFactory::Get(Production::TAGGED_TYPE);
  if (tagged_type->Parse(asnData, asnDataIndex, endStop))
  {
    mTaggedType = tagged_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "EncodingPrefixedType";
  LOG_START();
  auto encoding_prefixed_type =
    ProductionFactory::Get(Production::ENCODING_PREFIXED_TYPE);
  if (encoding_prefixed_type->Parse(asnData, asnDataIndex, endStop))
  {
    mEncodingPrefixedType = encoding_prefixed_type;
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
