#include "parser/AsnParser.hh"

#include "cxxopts.hpp"
#include "version_config.hh"

#include "spdlog/spdlog.h"

#include <iostream>

using namespace OpenASN;

int main(int argc, char* argv[])
{
  cxxopts::Options options(argv[0],
                           std::string(PROJECT_NAME) +
                           std::string(" v") +
                           std::string(PROJECT_VERSION) +
                           std::string(" - ") +
                           std::string(PROJECT_DESCRIPTION));

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

  spdlog::set_level(spdlog::level::debug);
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e %z] [%P:%t] [%L] [%s->%!()] %v");

  const size_t len = strlen(PROJECT_NAME) +
                     strlen(PROJECT_VERSION) +
                     strlen(PROJECT_DESCRIPTION) +
                     5;
  std::string banner_header(len, '=');

  SPDLOG_INFO(banner_header);
  SPDLOG_INFO("{} v{} - {}",
              PROJECT_NAME,
              PROJECT_VERSION,
              PROJECT_DESCRIPTION);
  SPDLOG_INFO(banner_header);
  SPDLOG_INFO(PROJECT_HOMEPAGE_URL);

  AsnParser p;

  for (const auto& f : asn_files)
  {
    p.Parse(f);
  }
}
