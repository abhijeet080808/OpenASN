#include "RelativeIRIType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
RelativeIRIType::
GetType() const
{
  return Production::RELATIVE_IRI_TYPE;
}

bool
RelativeIRIType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>&)
{
  // RelativeIRIType ::= RELATIVE-OID-IRI

  size_t starting_index = asnDataIndex;

  auto obj = "RELATIVE-OID-IRI";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
    return true;
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    return false;
  }
}
