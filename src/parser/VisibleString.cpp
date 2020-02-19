#include "VisibleString.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
VisibleString::
GetType() const
{
  return Production::VISIBLE_STRING;
}

bool
VisibleString::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // VisibleString

  LOG_START("VisibleString", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "VisibleString")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("VisibleString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("VisibleString", asnData);
    return false;
  }
}
