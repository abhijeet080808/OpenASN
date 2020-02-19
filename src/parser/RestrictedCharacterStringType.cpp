#include "RestrictedCharacterStringType.hh"

#include "ProductionFactory.hh"

#include "LoggingMacros.hh"
#include "spdlog/spdlog.h"

using namespace OpenASN;

Production
RestrictedCharacterStringType::
GetType() const
{
  return Production::RESTRICTED_CHARACTER_STRING_TYPE;
}

bool
RestrictedCharacterStringType::
Parse(AsnData& asnData, const std::vector<std::string>& endStop)
{
  // RestrictedCharacterStringType ::=
  //   BMPString
  // | GeneralString
  // | GraphicString
  // | IA5String
  // | ISO646String
  // | NumericString
  // | PrintableString
  // | TeletexString
  // | T61String
  // | UniversalString
  // | UTF8String
  // | VideotexString
  // | VisibleString

  LOG_START("BMPString", asnData);
  auto bmp_string =
    ProductionFactory::Get(Production::BMP_STRING);
  if (bmp_string->Parse(asnData, endStop))
  {
    mBMPString = bmp_string;
    LOG_PASS("BMPString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("BMPString", asnData);
  }

  LOG_START("GeneralString", asnData);
  auto general_string =
    ProductionFactory::Get(Production::GENERAL_STRING);
  if (general_string->Parse(asnData, endStop))
  {
    mGeneralString = general_string;
    LOG_PASS("GeneralString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("GeneralString", asnData);
  }

  LOG_START("GraphicString", asnData);
  auto graphic_string =
    ProductionFactory::Get(Production::GRAPHIC_STRING);
  if (graphic_string->Parse(asnData, endStop))
  {
    mGraphicString = graphic_string;
    LOG_PASS("GraphicString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("GraphicString", asnData);
  }

  LOG_START("IA5String", asnData);
  auto ia5_string =
    ProductionFactory::Get(Production::IA5_STRING);
  if (ia5_string->Parse(asnData, endStop))
  {
    mIA5String = ia5_string;
    LOG_PASS("IA5String", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("IA5String", asnData);
  }

  LOG_START("ISO646String", asnData);
  auto iso646_string =
    ProductionFactory::Get(Production::ISO646_STRING);
  if (iso646_string->Parse(asnData, endStop))
  {
    mISO646String = iso646_string;
    LOG_PASS("ISO646String", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("ISO646String", asnData);
  }

  LOG_START("NumericString", asnData);
  auto numeric_string =
    ProductionFactory::Get(Production::NUMERIC_STRING);
  if (numeric_string->Parse(asnData, endStop))
  {
    mNumericString = numeric_string;
    LOG_PASS("NumericString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("NumericString", asnData);
  }

  LOG_START("PrintableString", asnData);
  auto printable_string =
    ProductionFactory::Get(Production::PRINTABLE_STRING);
  if (printable_string->Parse(asnData, endStop))
  {
    mPrintableString = printable_string;
    LOG_PASS("PrintableString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("PrintableString", asnData);
  }

  LOG_START("T61String", asnData);
  auto t61_string =
    ProductionFactory::Get(Production::T61_STRING);
  if (t61_string->Parse(asnData, endStop))
  {
    mT61String = t61_string;
    LOG_PASS("T61String", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("T61String", asnData);
  }

  LOG_START("TeletexString", asnData);
  auto teletex_string =
    ProductionFactory::Get(Production::TELETEX_STRING);
  if (teletex_string->Parse(asnData, endStop))
  {
    mTeletexString = teletex_string;
    LOG_PASS("TeletexString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("TeletexString", asnData);
  }

  LOG_START("UniversalString", asnData);
  auto universal_string =
    ProductionFactory::Get(Production::UNIVERSAL_STRING);
  if (universal_string->Parse(asnData, endStop))
  {
    mUniversalString = universal_string;
    LOG_PASS("UniversalString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("UniversalString", asnData);
  }

  LOG_START("UTF8String", asnData);
  auto utf8_string =
    ProductionFactory::Get(Production::UTF8_STRING);
  if (utf8_string->Parse(asnData, endStop))
  {
    mUTF8String = utf8_string;
    LOG_PASS("UTF8String", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("UTF8String", asnData);
  }

  LOG_START("VideotexString", asnData);
  auto videotex_string =
    ProductionFactory::Get(Production::VIDEOTEX_STRING);
  if (videotex_string->Parse(asnData, endStop))
  {
    mVideotexString = videotex_string;
    LOG_PASS("VideotexString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("VideotexString", asnData);
  }

  LOG_START("VisibleString", asnData);
  auto visible_string =
    ProductionFactory::Get(Production::VISIBLE_STRING);
  if (visible_string->Parse(asnData, endStop))
  {
    mVisibleString = visible_string;
    LOG_PASS("VisibleString", asnData);
    return true;
  }
  else
  {
    LOG_FAIL("VisibleString", asnData);
  }

  return false;
}
