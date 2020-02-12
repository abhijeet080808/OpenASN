#include "ComponentType.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ComponentType::
GetType() const
{
  return Production::COMPONENT_TYPE;
}

bool
ComponentType::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // ComponentType ::=
  //   NamedType
  // | NamedType OPTIONAL
  // | NamedType DEFAULT Value
  // | COMPONENTS OF Type

  LOG_START("NamedType", asnData);
  auto named_type =
    ProductionFactory::Get(Production::NAMED_TYPE);
  if (named_type->Parse(asnData, endStop))
  {
    mNamedType = named_type;
    LOG_PASS("NamedType", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("NamedType", asnData);
  }

  return false;
}
