#include "EnumerationItem.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
EnumerationItem::
GetType() const
{
  return Production::ENUMERATION_ITEM;
}

bool
EnumerationItem::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // EnumerationItem ::= identifier | NamedNumber

  size_t starting_index = asnDataIndex;

  auto obj = "NamedNumber";
  LOG_START();
  auto named_number =
    ProductionFactory::Get(Production::NAMED_NUMBER);
  if (named_number->Parse(asnData, asnDataIndex, endStop))
  {
    mNamedNumber = named_number;
    LOG_PASS();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "Identifier";
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
