#include "BMPString.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
BMPString::
GetType() const
{
  return Production::BMP_STRING;
}

bool
BMPString::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>&,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("BMPString");

  // BMPString

  size_t starting_index = asnDataIndex;

  auto obj = "BMPString";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }
}
