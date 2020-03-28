#include "ArcIdentifier.hh"

#include "LoggingMacros.hh"
#include "ParseHelper.hh"
#include "ProductionFactory.hh"

#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
ArcIdentifier::
GetType() const
{
  return Production::ARC_IDENTIFIER;
}

bool
ArcIdentifier::
Parse(const std::vector<Word>& asnData,
      size_t& asnDataIndex,
      std::vector<std::string>& endStop,
      std::vector<std::string>& parsePath)
{
  parsePath.push_back("ArcIdentifier");

  // ArcIdentifier ::=
  //   integerUnicodeLabel
  // | non-integerUnicodeLabel

  size_t starting_index = asnDataIndex;

  auto obj = "IntegerUnicodeLabel";
  LOG_START();
  auto integer_unicode_label =
    ProductionFactory::Get(Production::INTEGER_UNICODE_LABEL);
  if (integer_unicode_label->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mIntegerUnicodeLabel = integer_unicode_label;
    LOG_PASS();
    parsePath.pop_back();
    return true;
  }
  else
  {
    LOG_FAIL();
  }

  obj = "NonIntegerUnicodeLabel";
  LOG_START();
  auto non_integer_unicode_label =
    ProductionFactory::Get(Production::NON_INTEGER_UNICODE_LABEL);
  if (non_integer_unicode_label->Parse(asnData, asnDataIndex, endStop, parsePath))
  {
    mNonIntegerUnicodeLabel = non_integer_unicode_label;
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
