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
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  auto asn_word = asnData.Peek();

  if (asn_word)
  {
    if (ParseHelper::HitEndStop(std::get<1>(asn_word.value()), endStop))
    {
      return false;
    }

    for (const auto& c : std::get<1>(asn_word.value()))
    {
      // Only numbers allowed
      if (!isdigit(c))
      {
        return false;
      }
    }

    // Leading zero not allowed
    if (std::get<1>(asn_word.value()).size() > 1 &&
        *((std::get<1>(asn_word.value())).begin()) == '0')
    {
      return false;
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
