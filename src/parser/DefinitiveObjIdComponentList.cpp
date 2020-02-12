#include "DefinitiveObjIdComponentList.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
DefinitiveObjIdComponentList::
GetType() const
{
  return Production::DEFINITIVE_OBJ_ID_COMPONENT_LIST;
}

bool
DefinitiveObjIdComponentList::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // DefinitiveObjIdComponentList ::=
  //   DefinitiveObjIdComponent
  // | DefinitiveObjIdComponent DefinitiveObjIdComponentList

  while (1)
  {
    LOG_START("DefinitiveObjIdComponent", asnData);
    auto definitive_obj_id_component =
      ProductionFactory::Get(Production::DEFINITIVE_OBJ_ID_COMPONENT);
    if (definitive_obj_id_component->Parse(asnData, endStop))
    {
      mDefinitiveObjIdComponent.push_back(definitive_obj_id_component);
      LOG_PASS("DefinitiveObjIdComponent", asnData);
    }
    else
    {
      LOG_FAIL("DefinitiveObjIdComponent", asnData);
      break;
    }
  }

  return !mDefinitiveObjIdComponent.empty();
}
