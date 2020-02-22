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
