#include "Type.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

#include "ParseHelper.hh"

using namespace OpenASN;

bool
Type::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // Type ::= BuiltinType | ReferencedType | ConstrainedType

  LOG_START("BuiltinType", asnData);
  BuiltinType builtin_type;
  if (builtin_type.Parse(asnData, endStop))
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
