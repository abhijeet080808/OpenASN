#include "NameForm.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

#include "ParseHelper.hh"

using namespace OpenASN;

bool
NameForm::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // NameForm ::= identifier

  LOG_START("Identifier", asnData);
  auto asn_word = asnData.PeekCurrent();
  if (asn_word)
  {
    if (ParseHelper::HitEndStop(std::get<1>(asn_word.value()), endStop))
    {
      LOG_FAIL("Identifier", asnData);
      return false;
    }

    if (mIdentifier.Parse(std::get<1>(asn_word.value())))
    {
      asnData.IncrementCurrentIndex();
      LOG_PASS("Identifier", asnData);
    }
    else
    {
      LOG_FAIL("Identifier", asnData);
      return false;
    }
  }
  else
  {
    LOG_FAIL("Identifier", asnData);
    return false;
  }

  return true;
}
