#include "TypeAssignment.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

#include "ParseHelper.hh"

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
  auto asn_word = asnData.PeekCurrent();
  if (asn_word)
  {
    if (ParseHelper::HitEndStop(std::get<1>(asn_word.value()), endStop))
    {
      LOG_FAIL("TypeReference", asnData);
      return false;
    }

    if (mTypeReference.Parse(std::get<1>(asn_word.value())))
    {
      asnData.IncrementCurrentIndex();
      LOG_PASS("TypeReference", asnData);
    }
    else
    {
      LOG_FAIL("TypeReference", asnData);
      return false;
    }
  }
  else
  {
    LOG_FAIL("TypeReference", asnData);
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
  if (mType.Parse(asnData, endStop))
  {
    LOG_PASS("Type", asnData);
  }
  else
  {
    LOG_FAIL("Type", asnData);
    return false;
  }

  return true;
}
