#include "DefinitiveOID.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
DefinitiveOID::
GetType() const
{
  return Production::DEFINITIVE_OID;
}

bool
DefinitiveOID::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("DefinitiveOID");

  // DefinitiveOID ::=
  // "{" DefinitiveObjIdComponentList "}"

  size_t starting_index = asnDataIndex;

  auto obj = "{";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  endStop.push_back("}");

  obj = "DefinitiveObjIdComponentList";
  LOG_START();
  auto definitive_obj_id_component_list =
    ProductionFactory::Get(Production::DEFINITIVE_OBJ_ID_COMPONENT_LIST);
  if (definitive_obj_id_component_list->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    endStop.pop_back();
    mDefinitiveObjIdComponentList = definitive_obj_id_component_list;
    LOG_PASS();
  }
  else
  {
    endStop.pop_back();
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "}";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }
}
