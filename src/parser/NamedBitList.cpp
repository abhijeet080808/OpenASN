#include "NamedBitList.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
NamedBitList::
GetType() const
{
  return Production::NAMED_BIT_LIST;
}

bool
NamedBitList::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // NamedBitList ::=
  //   NamedBit
  // | NamedBitList "," NamedBit

  while (1)
  {
    LOG_START("NamedBit", asnData);
    auto named_bit =
      ProductionFactory::Get(Production::NAMED_BIT);
    if (named_bit->Parse(asnData, endStop))
    {
      mNamedBit.push_back(named_bit);
      LOG_PASS("NamedBit", asnData);
    }
    else
    {
      LOG_FAIL("NamedBit", asnData);
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

  return !mNamedBit.empty();
}
