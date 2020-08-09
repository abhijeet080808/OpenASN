#include "Hstring.hh"

#include "ParseHelper.hh"

#include <cctype>

using namespace OpenASN;

Production
Hstring::
GetType() const
{
  return Production::HSTRING;
}

bool
Hstring::
Parse(
    size_t,
    bool,
    const std::vector<Word>& asnData,
    size_t& asnDataIndex,
    std::vector<std::string>& endStop,
    std::vector<std::string>&,
    ProductionParseHistory&)
{
  // Zero or more space separated number of A-F, 0-9 characters
  // enclosed within quotes and followed by H
  //
  // 'ABCD1100'H

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
      // Only A-F, 0-9 allowed
      if (c != 'A' &&
          c != 'B' &&
          c != 'C' &&
          c != 'D' &&
          c != 'E' &&
          c != 'F' &&
          c != '0' &&
          c != '1' &&
          c != '2' &&
          c != '3' &&
          c != '4' &&
          c != '5' &&
          c != '6' &&
          c != '7' &&
          c != '8' &&
          c != '9')
      {
        asnDataIndex = starting_index;
        return false;
      }
    }

    mValue = std::get<1>(asnData.at(asnDataIndex));
    ++asnDataIndex;
  }

  obj = "H";
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
