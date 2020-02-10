#include "ModuleIdentifier.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

#include "ParseHelper.hh"

using namespace OpenASN;

bool
ModuleIdentifier::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // ModuleIdentifier ::=
  // modulereference
  // DefinitiveIdentification

  LOG_START("ModuleReference", asnData);
  auto asn_word = asnData.PeekCurrent();
  if (asn_word)
  {
    if (ParseHelper::HitEndStop(std::get<1>(asn_word.value()), endStop))
    {
      LOG_FAIL("ModuleReference", asnData);
      return false;
    }

    if (mModuleReference.Parse(std::get<1>(asn_word.value())))
    {
      asnData.IncrementCurrentIndex();
      LOG_PASS("ModuleReference", asnData);
    }
    else
    {
      LOG_FAIL("ModuleReference", asnData);
      return false;
    }
  }
  else
  {
    LOG_FAIL("ModuleReference", asnData);
    return false;
  }

  LOG_START("DefinitiveIdentification", asnData);
	if (mDefinitiveIdentification.Parse(asnData, endStop))
	{
    LOG_PASS("DefinitiveIdentification", asnData);
  }
  else
  {
    LOG_FAIL("DefinitiveIdentification", asnData);
    return false;
	}

  return true;
}
