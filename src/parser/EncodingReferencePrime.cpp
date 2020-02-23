#include "EncodingReferencePrime.hh"

#include "ParseHelper.hh"

#include <cctype>

using namespace OpenASN;

Production
EncodingReferencePrime::
GetType() const
{
  return Production::ENCODING_REFERENCE_PRIME;
}

bool
EncodingReferencePrime::
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
