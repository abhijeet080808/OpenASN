#include "RelativeOIDType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
RelativeOIDType::
GetType() const
{
  return Production::RELATIVE_OID_TYPE;
}

bool
RelativeOIDType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>&)
{
  // RelativeOIDType ::= RELATIVE-OID

  size_t starting_index = asnDataIndex;

  auto obj = "RELATIVE-OID";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }
}
