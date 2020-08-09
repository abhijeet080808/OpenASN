#include "Number.hh"

#include "ParseHelper.hh"

#include <cctype>

using namespace OpenASN;

Production
Number::
GetType() const
{
  return Production::NUMBER;
}

bool
Number::
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

  std::vector<Word> asn_data;
  for (size_t i = asnDataIndex; i < asnDataIndex + 1 && i < asnData.size(); i++)
  {
    asn_data.push_back(asnData.at(i));
  }

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

int
Number::
parse(const std::vector<Word>& asnData)
{
  for (size_t i = 0; i < std::get<1>(asnData.at(0)).size(); i++)
  {
    char c = std::get<1>(asnData.at(0)).at(i);
    if (!isdigit(c))
    {
      return 0;
    }
    mValue.append(1, c);
  }

  // Leading zero not allowed
  if (std::get<1>(asnData.at(0)).size() > 1 &&
      *(std::get<1>(asnData.at(0)).begin()) == '0')
  {
    return 0;
  }

  return 1;
}
