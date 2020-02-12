#include "Type.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
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
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // Type ::= BuiltinType | ReferencedType | ConstrainedType

  LOG_START("BuiltinType", asnData);
  auto builtin_type =
    ProductionFactory::Get(Production::BUILTIN_TYPE);
  if (builtin_type->Parse(asnData, endStop))
  {
    mBuiltinType = builtin_type;
    LOG_PASS("BuiltinType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("BuiltinType", asnData);
  }

  return false;
}
