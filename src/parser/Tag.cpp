#include "Tag.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
Tag::
GetType() const
{
  return Production::TAG;
}

bool
Tag::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop)
{
  // Tag ::= "[" EncodingReference Class ClassNumber "]"

  size_t starting_index = asnDataIndex;

  auto obj = "[";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }

  endStop.push_back("]");

  obj = "EncodingReference";
  LOG_START();
  auto encoding_reference =
    ProductionFactory::Get(Production::ENCODING_REFERENCE);
  if (encoding_reference->Parse(asnData, asnDataIndex, endStop))
  {
    mEncodingReference = encoding_reference;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
    endStop.pop_back();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "Class";
  LOG_START();
  auto _class =
    ProductionFactory::Get(Production::CLASS);
  if (_class->Parse(asnData, asnDataIndex, endStop))
  {
    mClass = _class;
    LOG_PASS();
  }
  else
  {
    LOG_FAIL();
    endStop.pop_back();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "ClassNumber";
  LOG_START();
  auto class_number =
    ProductionFactory::Get(Production::CLASS_NUMBER);
  if (class_number->Parse(asnData, asnDataIndex, endStop))
  {
    mClassNumber = class_number;
    LOG_PASS();
    endStop.pop_back();
  }
  else
  {
    LOG_FAIL();
    endStop.pop_back();
    asnDataIndex = starting_index;
    return false;
  }

  obj = "]";
  LOG_START();
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    LOG_PASS();
    ++asnDataIndex;
    return true;
  }
  else
  {
    LOG_FAIL();
    asnDataIndex = starting_index;
    return false;
  }
}
