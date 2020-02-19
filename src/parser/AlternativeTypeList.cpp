#include "AlternativeTypeList.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
AlternativeTypeList::
GetType() const
{
  return Production::ALTERNATIVE_TYPE_LIST;
}

bool
AlternativeTypeList::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // AlternativeTypeList ::=
  //   NamedType
  // | AlternativeTypeList "," NamedType

  while (1)
  {
    LOG_START("NamedType", asnData);
    auto named_type =
      ProductionFactory::Get(Production::NAMED_TYPE);
    if (named_type->Parse(asnData, endStop))
    {
      mNamedType.push_back(named_type);
      LOG_PASS("NamedType", asnData);
    }
    else
    {
      LOG_FAIL("NamedType", asnData);
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

  return !mNamedType.empty();
}
