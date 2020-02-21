#include "RelativeIRIType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
RelativeIRIType::
GetType() const
{
  return Production::RELATIVE_IRI_TYPE;
}

bool
RelativeIRIType::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // RelativeIRIType ::= RELATIVE-OID-IRI

  LOG_START("RELATIVE-OID-IRI", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "RELATIVE-OID-IRI")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("RELATIVE-OID-IRI", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("RELATIVE-OID-IRI", asnData);
    return false;
  }
}
