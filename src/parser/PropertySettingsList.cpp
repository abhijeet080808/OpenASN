#include "PropertySettingsList.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
PropertySettingsList::
GetType() const
{
  return Production::PROPERTY_SETTINGS_LIST;
}

bool
PropertySettingsList::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("PropertySettingsList");

  // PropertySettingsList ::=
  //   PropertyAndSettingPair
  // | PropertySettingsList PropertyAndSettingPair

  size_t starting_index = asnDataIndex;

  while (1)
  {
    auto obj = "PropertyAndSettingPair";
    LOG_START();
    auto property_and_setting_pair =
      ProductionFactory::Get(Production::PROPERTY_AND_SETTING_PAIR);
    if (property_and_setting_pair->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mPropertyAndSettingPair.push_back(property_and_setting_pair);
      LOG_PASS();
    }
    else
    {
      LOG_FAIL();
      break;
    }
  }

  if (mPropertyAndSettingPair.empty())
  {
    asnDataIndex = starting_index;
    parsePath.pop_back();
    return false;
  }
  else
  {
    parsePath.pop_back();
    return true;
  }
}
