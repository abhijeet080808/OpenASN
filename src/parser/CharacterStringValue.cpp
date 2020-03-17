#include "CharacterStringValue.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
CharacterStringValue::
GetType() const
{
  return Production::CHARACTER_STRING_VALUE;
}

bool
CharacterStringValue::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("CharacterStringValue");

  // CharacterStringValue ::=
  //   RestrictedCharacterStringValue
  // | UnrestrictedCharacterStringValue

  size_t starting_index = asnDataIndex;

  auto obj = "RestrictedCharacterStringValue";
  LOG_START();
  auto restricted_character_string_value =
    ProductionFactory::Get(Production::RESTRICTED_CHARACTER_STRING_VALUE);
  if (restricted_character_string_value->Parse(asnData, asnDataIndex,
                                               endStop, parsePath))
  {
    mRestrictedCharacterStringValue = restricted_character_string_value;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "UnrestrictedCharacterStringValue";
  LOG_START();
  auto unrestricted_character_string_value =
    ProductionFactory::Get(Production::UNRESTRICTED_CHARACTER_STRING_VALUE);
  if (unrestricted_character_string_value->Parse(asnData, asnDataIndex,
                                                 endStop, parsePath))
  {
    mUnrestrictedCharacterStringValue = unrestricted_character_string_value;
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
