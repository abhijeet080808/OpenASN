#include "TaggedType.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
TaggedType::
GetType() const
{
  return Production::TAGGED_TYPE;
}

bool
TaggedType::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("TaggedType");

  // TaggedType ::=
  //   Tag Type
  // | Tag IMPLICIT Type
  // | Tag EXPLICIT Type

  size_t starting_index = asnDataIndex;

  auto obj = "Tag";
  LOG_START();
  auto tag =
    ProductionFactory::Get(Production::TAG);
  if (tag->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mTag = tag;
    LOG_PASS();
  }
  else
  {
    asnDataIndex = starting_index;
    LOG_FAIL();
    parsePath.pop_back();
    return false;
  }

  obj = "Type";
  LOG_START();
  auto type =
    ProductionFactory::Get(Production::TYPE);
  if (type->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mType = type;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "Implicit";
  LOG_START();
  auto implicit =
    ProductionFactory::Get(Production::IMPLICIT);
  if (implicit->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mImplicit = implicit;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
  }

  if (!mImplicit)
  {
    obj = "Explicit";
    LOG_START();
    auto _explicit =
      ProductionFactory::Get(Production::EXPLICIT);
    if (_explicit->Parse(asnData, asnDataIndex, endStop, parsePath))
    {
      mExplicit = _explicit;
      LOG_PASS();
    }
    else
    {
      asnDataIndex = starting_index;
      LOG_FAIL();
      parsePath.pop_back();
      return false;
    }
  }

  obj = "Type";
  LOG_START();
  type =
    ProductionFactory::Get(Production::TYPE);
  if (type->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mType = type;
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
