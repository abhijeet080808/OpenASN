#include "TypeAssignment.hh"

#include "CommonDefs.hh"
#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

bool
TypeAssignment::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // TypeAssignment ::=
  // typereference
  // "::="
  // Type

  LOG_START("TypeReference", asnData);
  auto type_reference =
    ProductionFactory::Get(Production::TYPE_REFERENCE);
  if (type_reference->Parse(asnData, endStop))
  {
    mTypeReference = type_reference;
    LOG_PASS("TypeReference", asnData);
  }
  else
  {
    LOG_FAIL("TypeReference", asnData);
    return false;
  }

  LOG_START(":", asnData);
  auto asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == ":")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS(":", asnData);
  }
  else
  {
    LOG_FAIL(":", asnData);
    return false;
  }

  LOG_START(":", asnData);
  asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == ":")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS(":", asnData);
  }
  else
  {
    LOG_FAIL(":", asnData);
    return false;
  }

  LOG_START("=", asnData);
  asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == "=")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("=", asnData);
  }
  else
  {
    LOG_FAIL("=", asnData);
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
    return false;
  }

  return true;
}
