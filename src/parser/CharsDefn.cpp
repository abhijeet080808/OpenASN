#include "CharsDefn.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
CharsDefn::
GetType() const
{
  return Production::CHARS_DEFN;
}

bool
CharsDefn::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("CharsDefn");

  // CharsDefn ::=
  //   cstring
  // | Quadruple
  // | Tuple
  // | DefinedValue

  size_t starting_index = asnDataIndex;

  auto obj = "Cstring";
  LOG_START();
  auto cstring =
    ProductionFactory::Get(Production::CSTRING);
  if (cstring->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mCstring = cstring;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "Quadruple";
  LOG_START();
  auto quadruple =
    ProductionFactory::Get(Production::QUADRUPLE);
  if (quadruple->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mQuadruple = quadruple;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "Tuple";
  LOG_START();
  auto tuple =
    ProductionFactory::Get(Production::TUPLE);
  if (tuple->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mTuple = tuple;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "DefinedValue";
  LOG_START();
  auto defined_value =
    ProductionFactory::Get(Production::DEFINED_VALUE);
  if (defined_value->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mDefinedValue = defined_value;
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
