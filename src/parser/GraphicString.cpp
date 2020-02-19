#include "GraphicString.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
GraphicString::
GetType() const
{
  return Production::GRAPHIC_STRING;
}

bool
GraphicString::
Parse(AsnData& asnData, const std::vector<std::string>&)
{
  // GraphicString

  LOG_START("GraphicString", asnData);
  auto asn_word = asnData.Peek();
  if (asn_word && std::get<1>(asn_word.value()) == "GraphicString")
  {
    asnData.IncrementCurrentIndex();
    LOG_PASS("GraphicString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("GraphicString", asnData);
    return false;
  }
}
