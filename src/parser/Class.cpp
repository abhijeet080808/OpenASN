#include "Class.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Class::
GetType() const
{
  return Production::CLASS;
}

bool
Class::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("Class");

  // Class ::=
  //   UNIVERSAL
  // | APPLICATION
  // | PRIVATE
  // | empty

  size_t starting_index = asnDataIndex;

  auto obj = "Universal";
  LOG_START();
  auto universal =
    ProductionFactory::Get(Production::UNIVERSAL);
  if (universal->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mUniversal = universal;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "Application";
  LOG_START();
  auto application =
    ProductionFactory::Get(Production::APPLICATION);
  if (application->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mApplication = application;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "Private";
  LOG_START();
  auto _private =
    ProductionFactory::Get(Production::PRIVATE);
  if (_private->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mPrivate = _private;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  asnDataIndex = starting_index;
  parsePath.pop_back();
  return true;
}
