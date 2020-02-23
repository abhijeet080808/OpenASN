#include "EncodingPrefix.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
EncodingPrefix::
GetType() const
{
  return Production::ENCODING_PREFIX;
}

bool
EncodingPrefix::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // EncodingPrefix ::= "[" EncodingReference EncodingInstruction "]"

  size_t starting_index = asnDataIndex;

  auto obj = "[";
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

  endStop.push_back("]");

  obj = "EncodingReference";
  LOG_START();
  auto encoding_reference =
    ProductionFactory::Get(Production::ENCODING_REFERENCE);
  if (encoding_reference->Parse(asnData, asnDataIndex, endStop))
  {
    mEncodingReference = encoding_reference;
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

#if 0
  obj = "EncodingInstruction";
  LOG_START();
  auto encoding_instruction =
    ProductionFactory::Get(Production::ENCODING_INSTRUCTION);
  if (encoding_instruction->Parse(asnData, asnDataIndex, endStop))
  {
    mEncodingInstruction = encoding_instruction;
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
#endif

  obj = "]";
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
