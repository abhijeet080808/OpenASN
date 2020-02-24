#include "ObjectDescriptor.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ObjectDescriptor::
GetType() const
{
  return Production::OBJECT_DESCRIPTOR;
}

bool
ObjectDescriptor::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>&)
{
  // ObjectDescriptor

  size_t starting_index = asnDataIndex;

  auto obj = "ObjectDescriptor";
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
