#include "EmbeddedPDVType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
EmbeddedPDVType::
GetType() const
{
  return Production::EMBEDDED_PDV_TYPE;
}

bool
EmbeddedPDVType::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // EmbeddedPDVType ::= EMBEDDED PDV

  LOG_START("EMBEDDED", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "EMBEDDED")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("EMBEDDED", asnData);
  }
  else
  {
    LOG_FAIL("EMBEDDED", asnData);
    return false;
  }

  LOG_START("PDV", asnData);
  asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "PDV")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("PDV", asnData);
  }
  else
  {
    LOG_FAIL("PDV", asnData);
    return false;
  }

  return true;
}
