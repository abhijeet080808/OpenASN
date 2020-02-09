#include "ModuleDefinition.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

bool
ModuleDefinition::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  std::vector<std::string> end_stop{ "DEFINITIONS" };
  end_stop.insert(std::end(end_stop), std::begin(endStop), std::end(endStop));

  LOG_START("ModuleIdentifier", asnData);
  if (mModuleIdentifier.Parse(asnData, end_stop))
  {
    LOG_PASS("ModuleIdentifier", asnData);
  }
  else
  {
    LOG_FAIL("ModuleIdentifier", asnData);
    return false;
  }

  LOG_START("DEFINITIONS", asnData);
  auto asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == "DEFINITIONS")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("DEFINITIONS", asnData);
  }
  else
  {
    LOG_FAIL("DEFINITIONS", asnData);
    return false;
  }

  LOG_START("::=", asnData);
  asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == "::=")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("::=", asnData);
  }
  else
  {
    LOG_FAIL("::=", asnData);
    return false;
  }

  LOG_START("BEGIN", asnData);
  asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == "BEGIN")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("BEGIN", asnData);
  }
  else
  {
    LOG_FAIL("BEGIN", asnData);
    return false;
  }

  return true;
}

