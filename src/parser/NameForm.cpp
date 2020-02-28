#include "NameForm.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
NameForm::
GetType() const
{
  return Production::NAME_FORM;
}

bool
NameForm::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // NameForm ::= identifier

  size_t starting_index = asnDataIndex;

  auto obj = "Identifier";
  LOG_START();
  auto identifier =
    ProductionFactory::Get(Production::IDENTIFIER);
  if (identifier->Parse(asnData, asnDataIndex, endStop))
  {
    mIdentifier = identifier;
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
