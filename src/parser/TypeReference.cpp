#include "TypeReference.hh"

#include "ParseHelper.hh"

#include <cctype>

using namespace OpenASN;

Production
TypeReference::
GetType() const
{
  return Production::TYPE_REFERENCE;
}

bool
TypeReference::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  auto asn_word = asnData.Peek();

  if (asn_word)
  {
    if (ParseHelper::HitEndStop(std::get<1>(asn_word.value()), endStop))
    {
      return false;
    }

    // First char must be upper case
    if (!isupper(*(std::get<1>(asn_word.value())).begin()))
    {
      return false;
    }

    // Last char can not be hyphen
    if ((*(std::get<1>(asn_word.value()).end()) - 1) == '-')
    {
      return false;
    }

    char last_c = 0;
    for (const auto& c : std::get<1>(asn_word.value()))
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

    mValue = std::get<1>(asn_word.value());
    asnData.IncrementCurrentIndex();

    return true;
  }
  else
  {
    return false;
  }
}
