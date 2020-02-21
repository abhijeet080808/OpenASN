#include "OctetStringType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
OctetStringType::
GetType() const
{
  return Production::OCTET_STRING_TYPE;
}

bool
OctetStringType::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // OctetStringType ::= OCTET STRING

  LOG_START("OCTET", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "OCTET")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("OCTET", asnData);
  }
  else
  {
    LOG_FAIL("OCTET", asnData);
    return false;
  }

  LOG_START("STRING", asnData);
  asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "STRING")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("STRING", asnData);
  }
  else
  {
    LOG_FAIL("STRING", asnData);
    return false;
  }

  return true;
}
