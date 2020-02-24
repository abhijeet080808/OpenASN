#include "Number.hh"

#include "ParseHelper.hh"

#include <cctype>

using namespace OpenASN;

Production
Number::
GetType() const
{
  return Production::NUMBER;
}

bool
Number::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  if (asnData.size() <= asnDataIndex)
  {
    return false;
  }

  if (ParseHelper::HitEndStop(std::get<1>(asnData.at(asnDataIndex)), endStop))
  {
    return false;
  }

  if (ParseHelper::IsReserved(std::get<1>(asnData.at(asnDataIndex))))
  {
    return false;
  }

  for (const auto& c : std::get<1>(asnData.at(asnDataIndex)))
  {
    // Only numbers allowed
    if (!isdigit(c))
    {
      return false;
    }
  }

  // Leading zero not allowed
  if (std::get<1>(asnData.at(asnDataIndex)).size() > 1 &&
      *(std::get<1>(asnData.at(asnDataIndex)).begin()) == '0')
  {
    return false;
  }

  mValue = std::get<1>(asnData.at(asnDataIndex));

  ++asnDataIndex;
  return true;
}
