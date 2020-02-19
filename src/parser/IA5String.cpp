#include "IA5String.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
IA5String::
GetType() const
{
  return Production::IA5_STRING;
}

bool
IA5String::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // IA5String

  LOG_START("IA5String", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "IA5String")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("IA5String", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("IA5String", asnData);
    return false;
  }
}
