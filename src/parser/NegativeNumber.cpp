#include "NegativeNumber.hh"

#include "ParseHelper.hh"

#include <cctype>

using namespace OpenASN;

Production
NegativeNumber::
GetType() const
{
  return Production::NEGATIVE_NUMBER;
}

bool
NegativeNumber::
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

  if (std::get<1>(asnData.at(asnDataIndex)).size() < 2)
  {
    return false;
  }

  bool first_char = true;
  for (const auto& c : std::get<1>(asnData.at(asnDataIndex)))
  {
    if (first_char)
    {
      // First char must be minus
      if (c != '-')
      {
        return false;
      }
      else
      {
        first_char = false;
      }
    }
    else
    {
      // Only numbers allowed
      if (!isdigit(c))
      {
        return false;
      }
    }
  }

  // Leading zero not allowed
  if (*(std::get<1>(asnData.at(asnDataIndex)).begin() + 1) == '0')
  {
    return false;
  }

  mValue = std::get<1>(asnData.at(asnDataIndex));
  // Do not store the leading negative sign
  mValue.erase(0, 1);

  ++asnDataIndex;
  return true;
}
