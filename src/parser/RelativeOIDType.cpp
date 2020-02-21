#include "RelativeOIDType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
RelativeOIDType::
GetType() const
{
  return Production::RELATIVE_OID_TYPE;
}

bool
RelativeOIDType::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // RelativeOIDType ::= RELATIVE-OID

  LOG_START("RELATIVE-OID", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "RELATIVE-OID")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("RELATIVE-OID", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("RELATIVE-OID", asnData);
    return false;
  }
}
