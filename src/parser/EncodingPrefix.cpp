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
    ++asnDataIndex;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
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

#if 0
  obj = "EncodingInstruction";
  LOG_START();
  auto encoding_instruction =
    ProductionFactory::Get(Production::ENCODING_INSTRUCTION);
  if (encoding_instruction->Parse(asnData, asnDataIndex, endStop))
  {
    mEncodingInstruction = encoding_instruction;
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
#endif

  obj = "]";
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
