#include "NamedValue.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
NamedValue::
GetType() const
{
  return Production::NAMED_VALUE;
}

bool
NamedValue::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("NamedValue");

  // NamedValue ::= identifier Value

  size_t starting_index = asnDataIndex;

  auto obj = "Identifier";
  LOG_START();
  auto identifier =
    ProductionFactory::Get(Production::IDENTIFIER);
  if (identifier->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mIdentifier = identifier;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "Value";
  LOG_START();
  auto value =
    ProductionFactory::Get(Production::VALUE);
  if (value->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mValue = value;
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