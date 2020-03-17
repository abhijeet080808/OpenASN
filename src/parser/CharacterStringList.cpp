#include "CharacterStringList.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
CharacterStringList::
GetType() const
{
  return Production::CHARACTER_STRING_LIST;
}

bool
CharacterStringList::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("CharacterStringList");

  // CharacterStringList ::= "{" CharSyms "}"

  size_t starting_index = asnDataIndex;

  auto obj = "{";
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
    parsePath.pop_back();
    return false;
  }

  endStop.push_back("}");

  obj = "CharSyms";
  LOG_START();
  auto char_syms =
    ProductionFactory::Get(Production::CHAR_SYMS);
  if (char_syms->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    endStop.pop_back();
    mCharSyms = char_syms;
    LOG_PASS();
  }
  else
  {
    endStop.pop_back();
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "}";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
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
