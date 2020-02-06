#include "parser/Parser.hh"

#include "cxxopts.hpp"

#include <iostream>

using namespace OpenASN;

int main(int argc, char* argv[])
{
  cxxopts::Options options(argv[0], "C++ ASN.1 Compiler");

  bool apple = false;

  options.add_options()
    ("a,apple", "an apple", cxxopts::value<bool>(apple));

  try
  {
    auto result = options.parse(argc, argv);
  }
  catch (const cxxopts::OptionException& e)
  {
    std::cout << "Error parsing options: " << e.what() << std::endl;
    exit(1);
  }

  std::cout << apple << std::endl;

  Parser p;
  p.Parse("Hello");
}
