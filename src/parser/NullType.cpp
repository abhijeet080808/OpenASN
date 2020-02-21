#include "NullType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
NullType::
GetType() const
{
  return Production::NULL_TYPE;
}

bool
NullType::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // NullType ::= Null

  LOG_START("NULL", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "NULL")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("NULL", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("NULL", asnData);
    return false;
  }
}
