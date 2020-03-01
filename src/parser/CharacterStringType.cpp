#include "CharacterStringType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
CharacterStringType::
GetType() const
{
  return Production::CHARACTER_STRING_TYPE;
}

bool
CharacterStringType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("CharacterStringType");

  // CharacterStringType ::=
  //   RestrictedCharacterStringType
  // | UnrestrictedCharacterStringType

  size_t starting_index = asnDataIndex;

  auto obj = "RestrictedCharacterStringType";
  LOG_START();
  auto restricted_character_string_type =
    ProductionFactory::Get(Production::RESTRICTED_CHARACTER_STRING_TYPE);
  if (restricted_character_string_type->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mRestrictedCharacterStringType = restricted_character_string_type;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "UnrestrictedCharacterStringType";
  LOG_START();
  auto unrestricted_character_string_type =
    ProductionFactory::Get(Production::UNRESTRICTED_CHARACTER_STRING_TYPE);
  if (unrestricted_character_string_type->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mUnrestrictedCharacterStringType = unrestricted_character_string_type;
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
