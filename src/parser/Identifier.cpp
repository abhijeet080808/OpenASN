#include "Identifier.hh"

#include <cctype>

using namespace OpenASN;

bool
Identifier::
Parse(const std::string& asnWord)
{
  // First char must be lower case
  if (!islower(*asnWord.begin()))
  {
    return false;
  }

  // Last char can not be hyphen
  if ((*asnWord.end() - 1) == '-')
  {
    return false;
  }

  char last_c = 0;
  for (const auto& c : asnWord)
  {
    // Only alphabets, numbers and hyphen allowed
    if (!isalnum(c) && c != '-')
    {
      return false;
    }

    // No 2 consequtive hyphens allowed
    if (c == '-' && c == last_c)
    {
      return false;
    }

    last_c = c;
  }

  mValue = asnWord;
  return true;
}
