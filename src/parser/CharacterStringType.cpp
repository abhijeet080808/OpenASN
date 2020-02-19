#include "CharacterStringType.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
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
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // CharacterStringType ::=
  //   RestrictedCharacterStringType
  // | UnrestrictedCharacterStringType

  LOG_START("RestrictedCharacterStringType", asnData);
  auto restricted_character_string_type =
    ProductionFactory::Get(Production::RESTRICTED_CHARACTER_STRING_TYPE);
  if (restricted_character_string_type->Parse(asnData, endStop))
  {
    mRestrictedCharacterStringType = restricted_character_string_type;
    LOG_PASS("RestrictedCharacterStringType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("RestrictedCharacterStringType", asnData);
  }

  LOG_START("UnrestrictedCharacterStringType", asnData);
  auto unrestricted_character_string_type =
    ProductionFactory::Get(Production::UNRESTRICTED_CHARACTER_STRING_TYPE);
  if (unrestricted_character_string_type->Parse(asnData, endStop))
  {
    mUnrestrictedCharacterStringType = unrestricted_character_string_type;
    LOG_PASS("UnrestrictedCharacterStringType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("UnrestrictedCharacterStringType", asnData);
  }

  return false;
}
