#include "AsnGenerator.hh"

using namespace OpenASN;

bool
AsnGenerator::
Generate(const std::shared_ptr<IProduction> production)
{
  return production.get() != nullptr;
}
