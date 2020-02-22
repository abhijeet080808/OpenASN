#include "DefinitiveObjIdComponent.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
DefinitiveObjIdComponent::
GetType() const
{
  return Production::DEFINITIVE_OBJ_ID_COMPONENT;
}

bool
DefinitiveObjIdComponent::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // DefinitiveObjIdComponent ::=
  //   NameForm
  // | DefinitiveNumberForm
  // | DefinitiveNameAndNumberForm

  // TODO Look at ITU X.680 08/2015 sec 32 to identify valid values
  // Also see ITU X.660 07/2011 annex A onwards

  size_t starting_index = asnDataIndex;

  auto obj = "NameForm";
  LOG_START();
  auto name_form =
    ProductionFactory::Get(Production::NAME_FORM);
  if (name_form->Parse(asnData, asnDataIndex, endStop))
  {
    mNameForm = name_form;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  // DefinitiveNumberForm
  // DefinitiveNameAndNumberForm

  asnDataIndex = starting_index;
  return false;
}
