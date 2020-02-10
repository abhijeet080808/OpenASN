#include "DefinitiveObjIdComponent.hh"

#include "CommonDefs.hh"
#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

bool
DefinitiveObjIdComponent::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // DefinitiveObjIdComponent ::=
  //   NameForm
  // | DefinitiveNumberForm
  // | DefinitiveNameAndNumberForm

  LOG_START("NameForm", asnData);
  auto name_form =
    ProductionFactory::Get(Production::NAME_FORM);
  if (name_form->Parse(asnData, endStop))
  {
    mNameForm = name_form;
    LOG_PASS("NameForm", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("NameForm", asnData);
  }

  // DefinitiveNumberForm
  // DefinitiveNameAndNumberForm

  return false;
}
