#include "SequenceOfType.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

#include "ParseHelper.hh"

using namespace OpenASN;

Production
SequenceOfType::
GetType() const
{
  return Production::SEQUENCE_OF_TYPE;
}

bool
SequenceOfType::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // SequenceOfType ::= SEQUENCE OF Type | SEQUENCE OF NamedType

  LOG_START("SEQUENCE", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "SEQUENCE")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("SEQUENCE", asnData);
  }
  else
  {
    LOG_FAIL("SEQUENCE", asnData);
    return false;
  }

  LOG_START("OF", asnData);
  asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "OF")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("OF", asnData);
  }
  else
  {
    LOG_FAIL("OF", asnData);
    return false;
  }

  LOG_START("Type", asnData);
  auto type =
    ProductionFactory::Get(Production::TYPE);
  if (type->Parse(asnData, endStop))
  {
    mType = type;
    LOG_PASS("Type", asnData);
  }
  else
  {
    LOG_FAIL("Type", asnData);
    LOG_START("NamedType", asnData);
    auto named_type =
      ProductionFactory::Get(Production::NAMED_TYPE);
    if (named_type->Parse(asnData, endStop))
    {
      mNamedType = named_type;
      LOG_PASS("NamedType", asnData);
    }
    else
    {
      LOG_FAIL("NamedType", asnData);
      return false;
    }
  }

  return true;
}
