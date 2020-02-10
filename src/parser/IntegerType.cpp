#include "IntegerType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

bool
IntegerType::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // IntegerType ::= INTEGER

  LOG_START("INTEGER", asnData);
  auto asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == "INTEGER")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("INTEGER", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("INTEGER", asnData);
    return false;
  }
}
