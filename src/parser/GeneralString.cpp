#include "GeneralString.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
GeneralString::
GetType() const
{
  return Production::GENERAL_STRING;
}

bool
GeneralString::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // GeneralString

  LOG_START("GeneralString", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "GeneralString")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("GeneralString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("GeneralString", asnData);
    return false;
  }
}
