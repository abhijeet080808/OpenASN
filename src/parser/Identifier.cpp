#include "Identifier.hh"

#include "ParseHelper.hh"

#include <cctype>

using namespace OpenASN;

Production
Identifier::
GetType() const
{
  return Production::IDENTIFIER;
}

bool
Identifier::
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

  // First char must be lower case
  if (!islower(*(std::get<1>(asnData.at(asnDataIndex)).begin())))
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
    // Only alphabets, numbers and hyphen allowed
    if (!isalnum(c) && c != '-')
    {
      return false;
    }

    // No 2 consequtive hyphens allowed
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
