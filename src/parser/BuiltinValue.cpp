#include "BuiltinValue.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
BuiltinValue::
GetType() const
{
  return Production::BUILTIN_VALUE;
}

bool
BuiltinValue::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("BuiltinValue");

  // BuiltinValue ::=
  //   BitStringValue
  // | BooleanValue
  // | CharacterStringValue
  // | ChoiceValue
  // | EmbeddedPDVValue
  // | EnumeratedValue
  // | ExternalValue
  // | InstanceOfValue
  // | IntegerValue
  // | IRIValue
  // | NullValue
  // | ObjectIdentifierValue
  // | OctetStringValue
  // | RealValue
  // | RelativeIRIValue
  // | RelativeOIDValue
  // | SequenceValue
  // | SequenceOfValue
  // | SetValue
  // | SetOfValue
  // | PrefixedValue
  // | TimeValue

  size_t starting_index = asnDataIndex;

  auto obj = "BitStringValue";
  LOG_START();
  auto bit_string_value =
    ProductionFactory::Get(Production::BIT_STRING_VALUE);
  if (bit_string_value->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mBitStringValue = bit_string_value;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "BooleanValue";
  LOG_START();
  auto boolean_value =
    ProductionFactory::Get(Production::BOOLEAN_VALUE);
  if (boolean_value->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mBooleanValue = boolean_value;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "CharacterStringValue";
  LOG_START();
  auto character_string_value =
    ProductionFactory::Get(Production::CHARACTER_STRING_VALUE);
  if (character_string_value->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mCharacterStringValue = character_string_value;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "ChoiceValue";
  LOG_START();
  auto choice_value =
    ProductionFactory::Get(Production::CHOICE_VALUE);
  if (choice_value->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mChoiceValue = choice_value;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "IntegerValue";
  LOG_START();
  auto integer_value =
    ProductionFactory::Get(Production::INTEGER_VALUE);
  if (integer_value->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mIntegerValue = integer_value;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  asnDataIndex = starting_index;
  parsePath.pop_back();
  return false;
}
