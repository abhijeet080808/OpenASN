#include "Includes.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Includes::
GetType() const
{
  return Production::INCLUDES;
}

bool
Includes::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>&,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("Includes");

  // Includes ::= INCLUDES | empty

  auto obj = "INCLUDES";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    mValue = obj;
    ++asnDataIndex;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
    parsePath.pop_back();
    return true;
  }
}
