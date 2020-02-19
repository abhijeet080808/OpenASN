#include "PrintableString.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
PrintableString::
GetType() const
{
  return Production::PRINTABLE_STRING;
}

bool
PrintableString::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // PrintableString

  LOG_START("PrintableString", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "PrintableString")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("PrintableString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("PrintableString", asnData);
    return false;
  }
}
