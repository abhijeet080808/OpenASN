#include "ExternalType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ExternalType::
GetType() const
{
  return Production::EXTERNAL_TYPE;
}

bool
ExternalType::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // ExternalType ::= EXTERNAL

  LOG_START("EXTERNAL", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "EXTERNAL")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("EXTERNAL", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("EXTERNAL", asnData);
    return false;
  }
}
