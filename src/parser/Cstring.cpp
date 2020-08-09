#include "Cstring.hh"

#include "ParseHelper.hh"

#include <cctype>
#include <sstream>

using namespace OpenASN;

Production
Cstring::
GetType() const
{
  return Production::CSTRING;
}

bool
Cstring::
Parse(
    size_t,
    bool,
    const std::vector<Word>& asnData,
    size_t& asnDataIndex,
    std::vector<std::string>& endStop,
    std::vector<std::string>&,
    ProductionParseHistory&)
{
  // Zero or more characters enclosed within double quotes where -
  // - double quote itself is represented by 2 consecutive double quotes
  // - all spaces after newline is ignored till a non space character is
  //   reached
  //
  // "abcd"
  // "abcd de
  //     fg"
  //
  // TODO - Support extended character set as defined by ISO/IEC 10646

  size_t starting_index = asnDataIndex;

  auto obj = "\"";
  if (ParseHelper::IsObjectPresent(obj, asnData, asnDataIndex))
  {
    ++asnDataIndex;
  }
  else
  {
    asnDataIndex = starting_index;
    return false;
  }

  std::stringstream ss;

  while (1)
  {
    if (asnData.size() <= asnDataIndex)
    {
      asnDataIndex = starting_index;
      return false;
    }

    if (ParseHelper::HitEndStop(std::get<1>(asnData.at(asnDataIndex)), endStop))
    {
      asnDataIndex = starting_index;
      return false;
    }

    if (ParseHelper::IsReserved(std::get<1>(asnData.at(asnDataIndex))))
    {
      asnDataIndex = starting_index;
      return false;
    }

    PrecedingInfo prec_info = std::get<0>(asnData.at(asnDataIndex));
    std::string asn_word = std::get<1>(asnData.at(asnDataIndex));
    int num_prec_whitespaces = std::get<3>(asnData.at(asnDataIndex));

    if (asn_word == "\"")
    {
      if (prec_info == PrecedingInfo::PRECEDED_BY_WHITESPACE)
      {
        ss << std::string(num_prec_whitespaces, ' ');
      }

      // check if next word is double quote too and it immediately follows
      // the first double quote
      if (asnData.size() > (asnDataIndex + 1) &&
          std::get<1>(asnData.at(asnDataIndex + 1)) == "\"" &&
          std::get<0>(asnData.at(asnDataIndex + 1)) ==
            PrecedingInfo::PRECEDED_BY_WHITESPACE &&
          std::get<3>(asnData.at(asnDataIndex + 1)) == 0)
      {
        ss << "\"";
        asnDataIndex = asnDataIndex + 2;
      }
      else // this is end of cstring
      {
        ++asnDataIndex;
        break;
      }
    }
    else if (prec_info == PrecedingInfo::PRECEDED_BY_WHITESPACE)
    {
      ss << std::string(num_prec_whitespaces, ' ');
      ss << asn_word;

      ++asnDataIndex;
    }
    else // prec_info == PrecedingInfo::PRECEDED_BY_NEWLINE
    {
      // all spaces after newline is consumed
      ss << asn_word;

      ++asnDataIndex;
    }
  }

  mValue = ss.str();

  return true;
}
