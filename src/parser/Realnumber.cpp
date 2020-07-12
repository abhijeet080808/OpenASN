#include "Realnumber.hh"

#include "ParseHelper.hh"

#include <cctype>

using namespace OpenASN;

namespace
{
  enum class RN_STATE
  {
    COEFF_BEFORE_DECIMAL,
    COEFF_AFTER_DECIMAL,
    E_SYMBOL,
    EXPONENT_SIGN,
    EXPONENT
  };
}

Production
Realnumber::
GetType() const
{
  return Production::REALNUMBER;
}

bool
Realnumber::
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

  std::vector<Word> asn_data;
  for (size_t i = asnDataIndex; i < asnDataIndex + 3 && i < asnData.size(); i++)
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
Realnumber::
parse(const std::vector<Word>& asnData)
{
  // Eg of real numbers in scientific notation -
  //
  // 10    10.    10.5
  // 10e6  10.e6  10.5e6
  // 10e+6 10.e+6 10.5e+6
  // 10e-6 10.e-6 10.5e-6
  //
  // e can be replaced with E
  // After e, leading zeros are not allowed
  //
  // In general the form is - <coefficient>[eE][+-]<exponent>
  //
  // AsnData is split on decimal point

  RN_STATE state = RN_STATE::COEFF_BEFORE_DECIMAL;
  bool e_parsed = false;

  for (size_t i = 0; i < std::get<1>(asnData.at(0)).size(); i++)
  {
    char c = std::get<1>(asnData.at(0)).at(i);
    switch (state)
    {
      case RN_STATE::COEFF_BEFORE_DECIMAL:
        if (isdigit(c))
        {
          // valid
          mCoeffBeforeDecimal.append(1, c);
        }
        else if (c == 'e' || c == 'E')
        {
          if (mCoeffBeforeDecimal.empty())
          {
            return 0;
          }
          e_parsed = true;
          state = RN_STATE::E_SYMBOL;
        }
        else
        {
          return 0;
        }
        break;

      case RN_STATE::E_SYMBOL:
        if (isdigit(c))
        {
          mExponent.append(1, c);
          state = RN_STATE::EXPONENT;
        }
        else if (c == '+' || c == '-')
        {
          mExponentSign.append(1, c);
          state = RN_STATE::EXPONENT_SIGN;
        }
        else
        {
          return 0;
        }
        break;

      case RN_STATE::EXPONENT_SIGN:
        if (isdigit(c))
        {
          mExponent.append(1, c);
          state = RN_STATE::EXPONENT;
        }
        else
        {
          return 0;
        }
        break;

      case RN_STATE::EXPONENT:
        if (isdigit(c))
        {
          // valid
          mExponent.append(1, c);
        }
        else
        {
          return 0;
        }
        break;

      default:
        return 0;
    }
  }

  bool decimal_present = false;
  if (state == RN_STATE::COEFF_BEFORE_DECIMAL &&
      asnData.size() == 3 &&
      std::get<1>(asnData.at(1)) == ".")
  {
    decimal_present = true;
    state = RN_STATE::COEFF_AFTER_DECIMAL;

    for (size_t i = 0; i < std::get<1>(asnData.at(2)).size(); i++)
    {
      char c = std::get<1>(asnData.at(2)).at(i);
      switch (state)
      {
        case RN_STATE::COEFF_AFTER_DECIMAL:
          if (isdigit(c))
          {
            // valid
            mCoeffAfterDecimal.append(1, c);
          }
          else if (c == 'e' || c == 'E')
          {
            e_parsed = true;
            state = RN_STATE::E_SYMBOL;
          }
          else
          {
            if (i == 0)
            {
              // The decimal point is NOT a COEFF_AFTER_DECIMAL scenario and is
              // present for other productions. Consider to have parsed upto
              // COEFF_BEFORE_DECIMAL and exit
              return 1;
            }
            else
            {
              return 0;
            }
          }
          break;

        case RN_STATE::E_SYMBOL:
          if (isdigit(c))
          {
            mExponent.append(1, c);
            state = RN_STATE::EXPONENT;
          }
          else if (c == '+' || c == '-')
          {
            mExponentSign.append(1, c);
            state = RN_STATE::EXPONENT_SIGN;
          }
          else
          {
            return 0;
          }
          break;

        case RN_STATE::EXPONENT_SIGN:
          if (isdigit(c))
          {
            mExponent.append(1, c);
            state = RN_STATE::EXPONENT;
          }
          else
          {
            return 0;
          }
          break;

        case RN_STATE::EXPONENT:
          if (isdigit(c))
          {
            // valid
            mExponent.append(1, c);
          }
          else
          {
            return 0;
          }
          break;

        default:
          return 0;
      }
    }
  }

  // e E should be followed by exponent
  if (e_parsed && mExponent.empty())
  {
    return 0;
  }

  // Leading zero not allowed
  if (mCoeffBeforeDecimal.size() > 1 && *(mCoeffBeforeDecimal.begin()) == '0')
  {
    return 0;
  }
  if (mExponent.size() > 1 && *(mExponent.begin()) == '0')
  {
    return 0;
  }

  if (decimal_present)
  {
    return 3;
  }
  else
  {
    return 1;
  }
}
