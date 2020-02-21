#include "IntegerType.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
IntegerType::
GetType() const
{
  return Production::INTEGER_TYPE;
}

bool
IntegerType::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // IntegerType ::=
  //   INTEGER
  // | INTEGER "{" NamedNumberList "}"

  LOG_START("INTEGER", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "INTEGER")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("INTEGER", asnData);
  }
  else
  {
    LOG_FAIL("INTEGER", asnData);
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
    return true;
  }

  std::vector<std::string> end_stop{ "}" };
  end_stop.insert(std::end(end_stop), std::begin(endStop), std::end(endStop));

  LOG_START("NamedNumberList", asnData);
  auto named_number_list =
    ProductionFactory::Get(Production::NAMED_NUMBER_LIST);
  if (named_number_list->Parse(asnData, end_stop))
  {
    mNamedNumberList = named_number_list;
    LOG_PASS("NamedNumberList", asnData);
  }
  else
  {
    LOG_FAIL("NamedNumberList", asnData);
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
