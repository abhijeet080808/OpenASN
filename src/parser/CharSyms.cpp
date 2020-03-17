#include "CharSyms.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
CharSyms::
GetType() const
{
  return Production::CHAR_SYMS;
}

bool
CharSyms::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("CharSyms");

  // CharSyms ::=
  //   CharsDefn
  // | CharSyms "," CharsDefn

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "CharsDefn";
    LOG_START();
    auto chars_defn =
      ProductionFactory::Get(Production::CHARS_DEFN);
    if (chars_defn->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mCharsDefn.push_back(chars_defn);
      LOG_PASS();
    }
    else
    {
      asnDataIndex = starting_index;
      LOG_FAIL();
      parsePath.pop_back();
      return false;
    }

    obj = ",";
    LOG_START();
    if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
    {
      ++asnDataIndex;
      LOG_PASS();
    }
    else
    {
      LOG_FAIL();
      break;
    }
  }

  if (mCharsDefn.empty())
  {
    asnDataIndex = starting_index;
    parsePath.pop_back();
    return false;
  }
  else
  {
    parsePath.pop_back();
    return true;
  }
}
