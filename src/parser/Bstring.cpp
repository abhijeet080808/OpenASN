#include "Bstring.hh"

#include "ParseHelper.hh"

#include <cctype>

using namespace OpenASN;

Production
Bstring::
GetType() const
{
  return Production::BSTRING;
}

bool
Bstring::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>&)
{
  // Zero or more space separated number of 0, 1 characters
  // enclosed within quotes and followed by B
  //
  // '01101100'B

  size_t starting_index = asnDataIndex;

  auto obj = "'";
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
  }
  else
  {
    asnDataIndex = starting_index;
    return false;
  }

  while (1)
  {
    obj = "'";
    if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
    {
      ++asnDataIndex;
      break;
    }

    if (asnData.size() <= asnDataIndex)
    {
      asnDataIndex = starting_index;
      return false;
    }

    if (ParseHelper::HitEndStop(std::get<1>(asnData.at(asnDataIndex)), endStop))
    {
      asnDataIndex = starting_index;
      return false;
    }

    if (ParseHelper::IsReserved(std::get<1>(asnData.at(asnDataIndex))))
    {
      asnDataIndex = starting_index;
      return false;
    }

    for (const auto& c : std::get<1>(asnData.at(asnDataIndex)))
    {
      // Only 0 and 1 allowed
      if (c != '0' && c != '1')
      {
        asnDataIndex = starting_index;
        return false;
      }
    }

    mValue = std::get<1>(asnData.at(asnDataIndex));
    ++asnDataIndex;
  }

  obj = "B";
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
  }
  else
  {
    asnDataIndex = starting_index;
    return false;
  }

  return true;
}
