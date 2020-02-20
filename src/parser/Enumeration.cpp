#include "Enumeration.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Enumeration::
GetType() const
{
  return Production::ENUMERATION;
}

bool
Enumeration::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // Enumeration ::= EnumerationItem | EnumerationItem "," Enumeration

  while (1)
  {
    LOG_START("EnumerationItem", asnData);
    auto enumeration_item =
      ProductionFactory::Get(Production::ENUMERATION_ITEM);
    if (enumeration_item->Parse(asnData, endStop))
    {
      mEnumerationItem.push_back(enumeration_item);
      LOG_PASS("EnumerationItem", asnData);
    }
    else
    {
      LOG_FAIL("EnumerationItem", asnData);
      return false;
    }

    LOG_START(",", asnData);
    auto asn_word = asnData.Peek();
    if (asn_word && std::get<1>(asn_word.value()) == ",")
    {
      asnData.IncrementCurrentIndex();
      LOG_PASS(",", asnData);
    }
    else
    {
      LOG_FAIL(",", asnData);
      break;
    }
  }

  return !mEnumerationItem.empty();
}
