#include "DefinitiveObjIdComponent.hh"

using namespace OpenASN;

bool
DefinitiveObjIdComponent::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  NameForm name_form;
  if (name_form.Parse(asnData, endStop))
  {
    mNameForm = name_form;
    return true;
  }

  /*
  DefinitiveNumberForm definitive_number_form;
  if (definitive_number_form.Parse(asnData,
                                   const std::vector<std::string>& endStop))
  {
    mDefinitiveNumberForm = definitive_number_form;
    return true;
  }

  DefinitiveNameAndNumberForm definitive_name_and_number_form;
  if (definitive_name_and_number_form.Parse(asnData,
                                            const std::vector<std::string>& endStop))
  {
    mDefinitiveNameAndNumberForm = definitive_name_and_number_form;
    return true;
  }
  */

  return false;
}
