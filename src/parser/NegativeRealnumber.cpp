#include "NegativeRealnumber.hh"

#include "ParseHelper.hh"

#include <cctype>

using namespace OpenASN;

Production
NegativeRealnumber::
GetType() const
{
  return Production::NEGATIVE_REALNUMBER;
}

bool
NegativeRealnumber::
Parse(const std::vector<Word>& asnData,
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

  // Real number can have 3 words where the second word is the decimal point
  std::vector<Word> asn_data;
  for (size_t i = asnDataIndex; i < asnDataIndex + 3 && i < asnData.size(); i++)
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
