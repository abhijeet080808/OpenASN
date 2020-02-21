#include "NamedNumberList.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
NamedNumberList::
GetType() const
{
  return Production::NAMED_NUMBER_LIST;
}

bool
NamedNumberList::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // NamedNumberList ::=
  //   NamedNumber
  // | NamedNumberList "," NamedNumber

  while (1)
  {
    LOG_START("NamedNumber", asnData);
    auto named_number =
      ProductionFactory::Get(Production::NAMED_NUMBER);
    if (named_number->Parse(asnData, endStop))
    {
      mNamedNumber.push_back(named_number);
      LOG_PASS("NamedNumber", asnData);
    }
    else
    {
      LOG_FAIL("NamedNumber", asnData);
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

  return !mNamedNumber.empty();
}
