#include "ModuleIdentifier.hh"

#include "ParseHelper.hh"

using namespace OpenASN;

bool
ModuleIdentifier::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  auto asn_word = asnData.Get();
  if (asn_word)
  {
    if (ParseHelper::HitEndStop(std::get<1>(asn_word.value()), endStop))
    {
      return false;
    }
    if (!mModuleReference.Parse(std::get<1>(asn_word.value())))
    {
      return false;
    }
  }
  else
  {
    return false;
  }

	if (mDefinitiveIdentification.Parse(asnData, endStop))
	{
    // ok
  }
  else
  {
    return false;
	}

  return true;
}
