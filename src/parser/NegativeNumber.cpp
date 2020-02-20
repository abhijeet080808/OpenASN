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
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  auto asn_word = asnData.Peek();

  if (asn_word)
  {
    if (ParseHelper::HitEndStop(std::get<1>(asn_word.value()), endStop))
    {
      return false;
    }

    if (std::get<1>(asn_word.value()).size() < 2)
    {
      return false;
    }

    bool first_char = true;
    for (const auto& c : std::get<1>(asn_word.value()))
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
    if (*((std::get<1>(asn_word.value())).begin() + 1) == '0')
    {
      return false;
    }

    mValue = std::get<1>(asn_word.value());
    // Do not store the negative sign
    mValue.erase(0, 1);
    asnData.IncrementCurrentIndex();

    return true;
  }
  else
  {
    return false;
  }
}
