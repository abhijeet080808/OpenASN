#include "NegativeNumber.hh"

#include "ParseHelper.hh"

#include <cctype>

using namespace OpenASN;

Production
NegativeNumber::
GetType() const
{
  return Production::NEGATIVE_NUMBER;
}

bool
NegativeNumber::
Parse(
    size_t,
    bool,
    const std::vector<Word>& asnData,
    size_t& asnDataIndex,
    std::vector<std::string>& endStop,
    std::vector<std::string>&,
    ProductionParseHistory&)
{
  if (asnData.size() <= asnDataIndex)
  {
    return false;
  }

  if (ParseHelper::HitEndStop(std::get<1>(asnData.at(asnDataIndex)), endStop))
  {
    return false;
  }

  if (ParseHelper::IsReserved(std::get<1>(asnData.at(asnDataIndex))))
  {
    return false;
  }

  if (std::get<1>(asnData.at(asnDataIndex)).size() < 2)
  {
    return false;
  }

  // Number can have 1 word
  std::vector<Word> asn_data;
  for (size_t i = asnDataIndex; i < asnDataIndex + 1 && i < asnData.size(); i++)
  {
    asn_data.push_back(asnData.at(i));
  }

  // First character of first word must be minus symbol
  if (std::get<1>(asn_data.at(0)).size() < 2 ||
      *std::get<1>(asn_data.at(0)).begin() != '-')
  {
    return false;
  }

  std::get<1>(asn_data.at(0)) =
    std::string(std::get<1>(asn_data.at(0)).begin() + 1,
                std::get<1>(asn_data.at(0)).end());

  int ret = parse(asn_data);
  if (ret != 0)
  {
    asnDataIndex += ret;
    return true;
  }
  else
  {
    return false;
  }
}
