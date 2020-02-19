#include "ChoiceType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

#include "ProductionFactory.hh"

using namespace OpenASN;

Production
ChoiceType::
GetType() const
{
  return Production::CHOICE_TYPE;
}

bool
ChoiceType::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // ChoiceType ::= CHOICE "{" AlternativeTypeLists "}"

  LOG_START("CHOICE", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "CHOICE")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("CHOICE", asnData);
  }
  else
  {
    LOG_FAIL("CHOICE", asnData);
    return false;
  }

  LOG_START("{", asnData);
  asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "{")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("{", asnData);
  }
  else
  {
    LOG_FAIL("{", asnData);
    return false;
  }

  std::vector<std::string> end_stop{ "}" };
  end_stop.insert(std::end(end_stop), std::begin(endStop), std::end(endStop));

  LOG_START("AlternativeTypeLists", asnData);
  auto alternative_type_lists =
    ProductionFactory::Get(Production::ALTERNATIVE_TYPE_LISTS);
  if (alternative_type_lists->Parse(asnData, end_stop))
  {
    mAlternativeTypeLists = alternative_type_lists;
    LOG_PASS("AlternativeTypeLists", asnData);
  }
  else
  {
    LOG_FAIL("AlternativeTypeLists", asnData);
    return false;
  }

  LOG_START("}", asnData);
  asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "}")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("}", asnData);
  }
  else
  {
    LOG_FAIL("}", asnData);
    return false;
  }

  return true;
}
