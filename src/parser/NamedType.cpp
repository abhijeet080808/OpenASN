#include "NamedType.hh"

#include "ParseHelper.hh"

using namespace OpenASN;

bool
NamedType::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  auto asn_word = asnData.Get();
  if (asn_word)
  {
    if (ParseHelper::HitEndStop(std::get<1>(asn_word.value()), endStop))
    {
      return false;
    }
    if (!mIdentifier.Parse(std::get<1>(asn_word.value())))
    {
      return false;
    }
  }
  else
  {
    return false;
  }

  // Type

  return true;
}
