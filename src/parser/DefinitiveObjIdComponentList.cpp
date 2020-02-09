#include "DefinitiveObjIdComponentList.hh"

using namespace OpenASN;

bool
DefinitiveObjIdComponentList::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  while (1)
  {
    DefinitiveObjIdComponent definitive_obj_id_component;
    if (definitive_obj_id_component.Parse(asnData, endStop))
    {
      mDefinitiveObjIdComponent.push_back(definitive_obj_id_component);
    }
    else
    {
      break;
    }
  }

  return true;
}
