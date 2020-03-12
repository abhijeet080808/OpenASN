#include "SettingName.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
SettingName::
GetType() const
{
  return Production::SETTING_NAME;
}

bool
SettingName::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("SettingName");

  // SettingName ::= psname

  size_t starting_index = asnDataIndex;

  auto obj = "PsName";
  LOG_START();
  auto ps_name =
    ProductionFactory::Get(Production::PS_NAME);
  if (ps_name->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mPsName = ps_name;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }
}
