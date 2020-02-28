#include "ComponentType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

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
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // ComponentType ::=
  //   NamedType
  // | NamedType OPTIONAL
  // | NamedType DEFAULT Value
  // | COMPONENTS OF Type

  size_t starting_index = asnDataIndex;

  auto obj = "NamedType";
  LOG_START();
  auto named_type =
    ProductionFactory::Get(Production::NAMED_TYPE);
  if (named_type->Parse(asnData, asnDataIndex, endStop))
  {
    mNamedType = named_type;
    LOG_PASS();
    return true;
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    return false;
  }
}
