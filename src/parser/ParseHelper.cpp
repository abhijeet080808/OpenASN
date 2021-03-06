#include "ParseHelper.hh"

#include <algorithm>
#include <set>

using namespace OpenASN;

bool
ParseHelper::
IsObjectPresent(const std::string& object,
                const std::vector<Word>& asnData,
                size_t& asnDataIndex)
{
  return (asnData.size() > asnDataIndex &&
          std::get<1>(asnData.at(asnDataIndex)) == object);
}

bool
ParseHelper::
HitEndStop(const std::string& asnWord,
           const std::vector<std::string>& endStop)
{
  return std::find(endStop.begin(), endStop.end(), asnWord) != endStop.end();
}

bool
ParseHelper::
IsReserved(const std::string& asnWord)
{
  // X.680 08/2015 sec 12.38
  // TODO optimize using set
  return asnWord == "ABSENT" ||
         asnWord == "ABSTRACT-SYNTAX" ||
         asnWord == "ALL" ||
         asnWord == "APPLICATION" ||
         asnWord == "AUTOMATIC" ||
         asnWord == "BEGIN" ||
         asnWord == "BIT" ||
         asnWord == "BMPString" ||
         asnWord == "BOOLEAN" ||
         asnWord == "BY" ||
         asnWord == "CHARACTER" ||
         asnWord == "CHOICE" ||
         asnWord == "CLASS" ||
         asnWord == "COMPONENT" ||
         asnWord == "COMPONENTS" ||
         asnWord == "CONSTRAINED" ||
         asnWord == "CONTAINING" ||
         asnWord == "DATE" ||
         asnWord == "DATE-TIME" ||
         asnWord == "DEFAULT" ||
         asnWord == "DEFINITIONS" ||
         asnWord == "DURATION" ||
         asnWord == "EMBEDDED" ||
         asnWord == "ENCODED" ||
         asnWord == "ENCODING-CONTROL" ||
         asnWord == "END" ||
         asnWord == "ENUMERATED" ||
         asnWord == "EXCEPT" ||
         asnWord == "EXPLICIT" ||
         asnWord == "EXPORTS" ||
         asnWord == "EXTENSIBILITY" ||
         asnWord == "EXTERNAL" ||
         asnWord == "FALSE" ||
         asnWord == "FROM" ||
         asnWord == "GeneralizedTime" ||
         asnWord == "GeneralString" ||
         asnWord == "GraphicString" ||
         asnWord == "IA5String" ||
         asnWord == "IDENTIFIER" ||
         asnWord == "IMPLICIT" ||
         asnWord == "IMPLIED" ||
         asnWord == "IMPORTS" ||
         asnWord == "INCLUDES" ||
         asnWord == "INSTANCE" ||
         asnWord == "INSTRUCTIONS" ||
         asnWord == "INTEGER" ||
         asnWord == "INTERSECTION" ||
         asnWord == "ISO646String" ||
         asnWord == "MAX" ||
         asnWord == "MIN" ||
         asnWord == "MINUS-INFINITY" ||
         asnWord == "NOT-A-NUMBER" ||
         asnWord == "NULL" ||
         asnWord == "NumericString" ||
         asnWord == "OBJECT" ||
         asnWord == "ObjectDescriptor" ||
         asnWord == "OCTET" ||
         asnWord == "OF" ||
         asnWord == "OID-IRI" ||
         asnWord == "OPTIONAL" ||
         asnWord == "PATTERN" ||
         asnWord == "PDV" ||
         asnWord == "PLUS-INFINITY" ||
         asnWord == "PRESENT" ||
         asnWord == "PrintableString" ||
         asnWord == "PRIVATE" ||
         asnWord == "REAL" ||
         asnWord == "RELATIVE-OID" ||
         asnWord == "RELATIVE-OID-IRI" ||
         asnWord == "SEQUENCE" ||
         asnWord == "SET" ||
         asnWord == "SETTINGS" ||
         asnWord == "SIZE" ||
         asnWord == "STRING" ||
         asnWord == "SYNTAX" ||
         asnWord == "T61String" ||
         asnWord == "TAGS" ||
         asnWord == "TeletexString" ||
         asnWord == "TIME" ||
         asnWord == "TIME-OF-DAY" ||
         asnWord == "TRUE" ||
         asnWord == "TYPE-IDENTIFIER" ||
         asnWord == "UNION" ||
         asnWord == "UNIQUE" ||
         asnWord == "UNIVERSAL" ||
         asnWord == "UniversalString" ||
         asnWord == "UTCTime" ||
         asnWord == "UTF8String" ||
         asnWord == "VideotexString" ||
         asnWord == "VisibleString" ||
         asnWord == "WITH";
}

bool
ParseHelper::
IsLexicalItem(char c)
{
  // X.680 08/2015 sec 12.37
  return c == '{' ||
         c == '}' ||
         c == '<' ||
         c == '>' ||
         c == ',' ||
         c == '.' ||
         c == '/' ||
         c == '(' ||
         c == ')' ||
         c == '[' ||
         c == ']' ||
         c == '-' ||
         c == ':' ||
         c == '=' ||
         c == '"' ||
         c == '\''||
      // c == ' ' ||
         c == ';' ||
         c == '@' ||
         c == '|' ||
         c == '!' ||
         c == '^';
}

bool
ParseHelper::
IsWhitespace(char c)
{
  // X.680 08/2015 sec 12.1.6
  return c == 0x09 || // horizontal tab
         c == 0x20;   // space
}

bool
ParseHelper::
IsNewline(char c)
{
  // X.680 08/2015 sec 12.1.6
  return c == 0x0a || // line feed
         c == 0x0b || // vertical tab
         c == 0x0c || // form feed
         c == 0x0d;   // carriage return
}
