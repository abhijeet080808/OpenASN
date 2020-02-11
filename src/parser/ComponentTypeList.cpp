#include "ComponentTypeList.hh"

#include "CommonDefs.hh"
#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

bool
ComponentTypeList::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // ComponentTypeList ::=
  //   ComponentType
  // | ComponentTypeList "," ComponentType

  while (1)
  {
    LOG_START("ComponentType", asnData);
    auto component_type =
      ProductionFactory::Get(Production::COMPONENT_TYPE);
    if (component_type->Parse(asnData, endStop))
    {
      mComponentType.push_back(component_type);
      LOG_PASS("ComponentType", asnData);
    }
    else
    {
      LOG_FAIL("ComponentType", asnData);
      break;
    }

    LOG_START(",", asnData);
    auto asn_word = asnData.Peek();
    if (asn_word && std::get<1>(asn_word.value()) == ",")
    {
      asnData.IncrementCurrentIndex();
      LOG_PASS(",", asnData);
    }
    else
    {
      LOG_FAIL(",", asnData);
      break;
    }
  }

  return !mComponentType.empty();
}
