#include "Value.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Value::
GetType() const
{
  return Production::VALUE;
}

bool
Value::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("Value");

  // Value ::= BuiltinValue | ReferencedValue | ObjectClassFieldValue

  size_t starting_index = asnDataIndex;

  auto obj = "BuiltinValue";
  LOG_START();
  auto builtin_value =
    ProductionFactory::Get(Production::BUILTIN_VALUE);
  if (builtin_value->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mBuiltinValue = builtin_value;
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
