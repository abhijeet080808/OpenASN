#include "SequenceType.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

#include "ParseHelper.hh"

using namespace OpenASN;

bool
SequenceType::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // SequenceType ::=
  //   SEQUENCE "{" "}"
  // | SEQUENCE "{" ExtensionAndException OptionalExtensionMarker "}"
  // | SEQUENCE "{" ComponentTypeLists "}"

  LOG_START("SEQUENCE", asnData);
  auto asn_word = asnData.PeekCurrent();
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

  LOG_START("{", asnData);
  asn_word = asnData.PeekCurrent();
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

  LOG_START("}", asnData);
  asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == "}")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("}", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("}", asnData);
  }

  std::vector<std::string> end_stop{ "}" };
  end_stop.insert(std::end(end_stop), std::begin(endStop), std::end(endStop));

  LOG_START("ComponentTypeLists", asnData);
  ComponentTypeLists component_type_lists;
  if (component_type_lists.Parse(asnData, end_stop))
  {
    mComponentTypeLists = component_type_lists;
    LOG_PASS("ComponentTypeLists", asnData);
  }
  else
  {
    LOG_FAIL("ComponentTypeLists", asnData);
  }

  // ExtensionAndException OptionalExtensionMarker

  LOG_START("}", asnData);
  asn_word = asnData.PeekCurrent();
  if (asn_word && std::get<1>(asn_word.value()) == "}")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("}", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("}", asnData);
    return false;
  }
}
