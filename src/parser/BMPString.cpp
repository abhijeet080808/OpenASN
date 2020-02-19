#include "BMPString.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
BMPString::
GetType() const
{
  return Production::BMP_STRING;
}

bool
BMPString::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // BMPString

  LOG_START("BMPString", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "BMPString")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("BMPString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("BMPString", asnData);
    return false;
  }
}
