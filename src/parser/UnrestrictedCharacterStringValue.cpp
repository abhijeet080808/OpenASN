#include "UnrestrictedCharacterStringValue.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
UnrestrictedCharacterStringValue::
GetType() const
{
  return Production::UNRESTRICTED_CHARACTER_STRING_VALUE;
}

bool
UnrestrictedCharacterStringValue::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("UnrestrictedCharacterStringValue");

  // UnrestrictedCharacterStringValue ::= SequenceValue

  size_t starting_index = asnDataIndex;

  auto obj = "SequenceValue";
  LOG_START();
  auto sequence_value =
    ProductionFactory::Get(Production::SEQUENCE_VALUE);
  if (sequence_value->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mSequenceValue = sequence_value;
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
