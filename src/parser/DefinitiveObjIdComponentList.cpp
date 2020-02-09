#include "DefinitiveObjIdComponentList.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

bool
DefinitiveObjIdComponentList::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  while (1)
  {
    LOG_START("DefinitiveObjIdComponent", asnData);
    DefinitiveObjIdComponent definitive_obj_id_component;
    if (definitive_obj_id_component.Parse(asnData, endStop))
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

  return true;
}
