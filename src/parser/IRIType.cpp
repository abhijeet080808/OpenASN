#include "IRIType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
IRIType::
GetType() const
{
  return Production::IRI_TYPE;
}

bool
IRIType::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // IRIType ::= OID-IRI

  LOG_START("OID-IRI", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "OID-IRI")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("OID-IRI", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("OID-IRI", asnData);
    return false;
  }
}
