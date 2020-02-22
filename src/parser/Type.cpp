#include "Type.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Type::
GetType() const
{
  return Production::TYPE;
}

bool
Type::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // Type ::= BuiltinType | ReferencedType | ConstrainedType

  size_t starting_index = asnDataIndex;

  auto obj = "BuiltinType";
  LOG_START();
  auto builtin_type =
    ProductionFactory::Get(Production::BUILTIN_TYPE);
  if (builtin_type->Parse(asnData, asnDataIndex, endStop))
  {
    mBuiltinType = builtin_type;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }
}
