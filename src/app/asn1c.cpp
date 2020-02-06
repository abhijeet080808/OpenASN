#include "parser/Parser.hh"

#include "cxxopts.hpp"

#include <iostream>

using namespace OpenASN;

int main(int argc, char* argv[])
{
  cxxopts::Options options(argv[0], "C++ ASN.1 Compiler");

  std::vector<std::string> asn_files;

  options.add_options()
    ("h,help", "Print help")
    ("a,asn", "Specify one or more ASN.1 files, separating multiple files "
     "with a comma",
     cxxopts::value<std::vector<std::string>>(),
     "FILE1[,FILE2,...]");

  try
  {
    cxxopts::ParseResult result = options.parse(argc, argv);

    if (result.count("help"))
    {
      std::cout << options.help({""}) << std::endl;
      exit(0);
    }

    if (result.count("a"))
    {
      asn_files = result["a"].as<std::vector<std::string>>();
    }
    else
    {
      std::cout << std::endl << "Missing option -a"
                << std::endl << std::endl
                << options.help() << std::endl;
      exit(1);
    }

    if (argc > 1)
    {
      std::cout << std::endl;
      for (int i = 1; i < argc; i++)
      {
        std::cout << "Unparsed option: " << argv[i] << std::endl;
      }
      std::cout << std::endl << options.help() << std::endl;
      exit(1);
    }
  }
  catch (const cxxopts::OptionException& e)
  {
    std::cout << "Error parsing options: " << e.what() << std::endl;
    exit(1);
  }

  Parser p;

  for (const auto& f : asn_files)
  {
    p.Parse(f);
  }
}
