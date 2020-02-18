#include "BitStringType.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
BitStringType::
GetType() const
{
  return Production::BIT_STRING_TYPE;
}

bool
BitStringType::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // BitStringType ::=
  //   BIT STRING
  // | BIT STRING "{" NamedBitList "}"

  LOG_START("BIT", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "BIT")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("BIT", asnData);
  }
  else
  {
    LOG_FAIL("BIT", asnData);
    return false;
  }

  LOG_START("STRING", asnData);
  asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "STRING")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("STRING", asnData);
  }
  else
  {
    LOG_FAIL("STRING", asnData);
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

  LOG_START("NamedBitList", asnData);
  auto named_bit_list =
    ProductionFactory::Get(Production::NAMED_BIT_LIST);
  if (named_bit_list->Parse(asnData, end_stop))
  {
    mNamedBitList = named_bit_list;
    LOG_PASS("NamedBitList", asnData);
  }
  else
  {
    LOG_FAIL("NamedBitList", asnData);
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
