#include "PropertyAndSettingPair.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
PropertyAndSettingPair::
GetType() const
{
  return Production::PROPERTY_AND_SETTING_PAIR;
}

bool
PropertyAndSettingPair::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("PropertyAndSettingPair");

  // PropertyAndSettingPair ::= PropertyName "=" SettingName

  size_t starting_index = asnDataIndex;

  auto obj = "PropertyName";
  LOG_START();
  auto property_name =
    ProductionFactory::Get(Production::PROPERTY_NAME);
  if (property_name->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mPropertyName = property_name;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "=";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "SettingName";
  LOG_START();
  auto setting_name =
    ProductionFactory::Get(Production::SETTING_NAME);
  if (setting_name->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mSettingName = setting_name;
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
