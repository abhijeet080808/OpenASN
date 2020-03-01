#include "DefinitiveObjIdComponentList.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

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
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("DefinitiveObjIdComponentList");

  // DefinitiveObjIdComponentList ::=
  //   DefinitiveObjIdComponent
  // | DefinitiveObjIdComponent DefinitiveObjIdComponentList

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "DefinitiveObjIdComponent";
    LOG_START();
    auto definitive_obj_id_component =
      ProductionFactory::Get(Production::DEFINITIVE_OBJ_ID_COMPONENT);
    if (definitive_obj_id_component->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mDefinitiveObjIdComponent.push_back(definitive_obj_id_component);
      LOG_PASS();
    }
    else
    {
      LOG_FAIL();
      break;
    }
  }

  if (mDefinitiveObjIdComponent.empty())
  {
    asnDataIndex = starting_index;
    parsePath.pop_back();
    return false;
  }
  else
  {
    parsePath.pop_back();
    return true;
  }
}
