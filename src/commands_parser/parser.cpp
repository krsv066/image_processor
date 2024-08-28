#include "parser.h"

CmdParams Parser::Parse(int argc, char **argv) {
    CmdParams cmd_params;
    std::vector<FilterParams> filters_params;

    try {
        if (argc < 3) {
            throw std::runtime_error("Not enough arguments");
        }

        cmd_params.InputFilePath = argv[1];
        cmd_params.OutputFilePath = argv[2];

        int i = 3;
        while (i < argc) {
            std::string filter = argv[i];

            if (filter == "-crop") {
                if (i + 2 >= argc) {
                    throw std::runtime_error("Not enough arguments");
                }
                filters_params.emplace_back(FilterParams{
                    .Filter = FilterType::Crop,
                    .IntParam1 = std::atoll(argv[i + 1]),
                    .IntParam2 = std::atoll(argv[i + 2]),
                });
                i += 3;
            }

            else if (filter == "-gs") {
                filters_params.emplace_back(FilterParams{
                    .Filter = FilterType::Grayscale,
                });
                ++i;
            }

            else if (filter == "-neg") {
                filters_params.emplace_back(FilterParams{
                    .Filter = FilterType::Negative,
                });
                ++i;
            }

            else if (filter == "-sharp") {
                filters_params.emplace_back(FilterParams{
                    .Filter = FilterType::Sharpening,
                });
                ++i;
            }

            else if (filter == "-edge") {
                if (i + 1 >= argc) {
                    throw std::runtime_error("Not enough arguments");
                }
                filters_params.emplace_back(FilterParams{
                    .Filter = FilterType::EdgeDetection,
                    .DoubleParam = std::atof(argv[i + 1]),
                });
                i += 2;
            }

            else if (filter == "-blur") {
                if (i + 1 >= argc) {
                    throw std::runtime_error("Not enough arguments");
                }
                filters_params.emplace_back(FilterParams{
                    .Filter = FilterType::GaussianBlur,
                    .DoubleParam = std::atof(argv[i + 1]),
                });
                i += 2;
            }

            else if (filter == "-crystal") {
                if (i + 1 >= argc) {
                    throw std::runtime_error("Not enough arguments");
                }
                filters_params.emplace_back(FilterParams{
                    .Filter = FilterType::Crystallize,
                    .IntParam1 = std::atoll(argv[i + 1]),
                });
                i += 2;
            }

            else {
                throw std::runtime_error("Invalid arguments");
            }
        }

        cmd_params.FiltersParams = filters_params;

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return cmd_params;
}
