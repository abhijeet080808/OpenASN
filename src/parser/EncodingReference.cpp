#include "EncodingReference.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
EncodingReference::
GetType() const
{
  return Production::ENCODING_REFERENCE;
}

bool
EncodingReference::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // EncodingReference ::=
  //   encodingreference ":"
  // | empty

  size_t starting_index = asnDataIndex;

  auto obj = "EncodingReferencePrime";
  LOG_START();
  auto encoding_reference_prime =
    ProductionFactory::Get(Production::ENCODING_REFERENCE_PRIME);
  if (encoding_reference_prime->Parse(asnData, asnDataIndex, endStop))
  {
    mEncodingReferencePrime = encoding_reference_prime;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    return true;
  }

  obj = ":";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
    return true;
  }
  else
  {
    mEncodingReferencePrime.reset();
    asnDataIndex = starting_index;
    LOG_FAIL();
    return true;
  }
}
