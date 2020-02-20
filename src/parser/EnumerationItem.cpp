#include "EnumerationItem.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
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
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // EnumerationItem ::= identifier | NamedNumber

  LOG_START("Identifier", asnData);
  auto identifier =
    ProductionFactory::Get(Production::IDENTIFIER);
  if (identifier->Parse(asnData, endStop))
  {
    LOG_PASS("Identifier", asnData);
    // Check if NamedNumber follows
    LOG_START("(", asnData);
    auto asn_word = asnData.Peek();
    if (asn_word && std::get<1>(asn_word.value()) == "(")
    {
      LOG_PASS("(", asnData);
      // Roll back reading of identifier for it to be read by NamedNumber
      // below
      asnData.DecrementCurrentIndex();
    }
    else
    {
      LOG_FAIL("(", asnData);
      mIdentifier = identifier;
      return true;
    }
  }
  else
  {
    LOG_FAIL("Identifier", asnData);
    // Both identifier and NamedNumber options should read identifier as
    // first item
    return false;
  }

  LOG_START("NamedNumber", asnData);
  auto named_number =
    ProductionFactory::Get(Production::NAMED_NUMBER);
  if (named_number->Parse(asnData, endStop))
  {
    mNamedNumber = named_number;
    LOG_PASS("NamedNumber", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("NamedNumber", asnData);
  }

  return false;
}
