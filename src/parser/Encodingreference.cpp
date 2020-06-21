#include "Encodingreference.hh"

#include "ParseHelper.hh"

#include <cctype>

using namespace OpenASN;

Production
Encodingreference::
GetType() const
{
  return Production::ENCODINGREFERENCE;
}

bool
Encodingreference::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>&,
      ProductionParseHistory&)
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

  // Last char can not be hyphen
  if (*(std::get<1>(asnData.at(asnDataIndex)).end() - 1) == '-')
  {
    return false;
  }

  char last_c = 0;
  for (const auto& c : std::get<1>(asnData.at(asnDataIndex)))
  {
    // Only upper case alphabets and hyphen allowed
    if (!isupper(c) && c != '-')
    {
      return false;
    }

    // No 2 consecutive hyphens allowed
    if (c == '-' && c == last_c)
    {
      return false;
    }

    last_c = c;
  }

  mValue = std::get<1>(asnData.at(asnDataIndex));
  ++asnDataIndex;

  return true;
}
