#include "parser/AsnParser.hh"
#include "generator/AsnGenerator.hh"

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
  bool parse_only_mode = false;

  options.add_options()
    ("h,help", "Print help")
    ("a,asn", "Specify one or more ASN.1 files, separating multiple files "
     "with a comma",
     cxxopts::value<std::vector<std::string>>(),
     "FILE1[,FILE2,...]")
    ("p,parse", "Parse ASN.1 files but skip generating CPP files");

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

    if (result.count("parse"))
    {
      parse_only_mode = true;
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
  // [2020-02-09 21:15:00.169] [66212] [I main() asn1c.cpp] Log text
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%P] [%L %!() %s] %v");

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
  AsnGenerator g;

  for (const auto& f : asn_files)
  {
    auto module_definition = p.Parse(f);
    if (parse_only_mode)
    {
      if (module_definition)
      {
        SPDLOG_INFO("Parse \"{}\" completed", f);
      }
      else
      {
        SPDLOG_INFO("Parse \"{}\" failed", f);
        exit(1);
      }
    }
    else
    {
      if (module_definition)
      {
        SPDLOG_INFO("Parse \"{}\" completed", f);
        g.Generate(dynamic_cast<ModuleDefinition*>(module_definition.get()));
      }
      else
      {
        SPDLOG_INFO("Parse \"{}\" failed", f);
        exit(1);
      }
    }
  }
}
