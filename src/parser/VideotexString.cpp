#include "VideotexString.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
VideotexString::
GetType() const
{
  return Production::VIDEOTEX_STRING;
}

bool
VideotexString::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // VideotexString

  LOG_START("VideotexString", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "VideotexString")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("VideotexString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("VideotexString", asnData);
    return false;
  }
}
