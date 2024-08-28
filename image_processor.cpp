#include "src/image/image.h"
#include "src/commands_parser/parser.h"
#include "src/filters/negative_filter.h"
#include "src/filters/grayscale_filter.h"
#include "src/filters/sharpening_filter.h"
#include "src/filters/edge_detection_filter.h"
#include "src/filters/crop_filter.h"
#include "src/filters/gaussian_blur_filter.h"
#include "src/filters/crystallize_filter.h"

int main(int argc, char **argv) {
    Parser cmd_parser;
    CmdParams cmd_params = cmd_parser.Parse(argc, argv);
    std::vector<FilterParams> params = cmd_params.FiltersParams;

    try {
        Image image(cmd_params.InputFilePath);

        for (const auto &param : params) {
            switch (param.Filter) {
                case FilterType::Crop: {
                    Crop filter;
                    filter.Process(image, param.IntParam1, param.IntParam2, 0);
                    break;
                }
                case FilterType::Grayscale: {
                    Grayscale filter;
                    filter.Process(image, 0, 0, 0);
                    break;
                }
                case FilterType::Negative: {
                    Negative filter;
                    filter.Process(image, 0, 0, 0);
                    break;
                }
                case FilterType::Sharpening: {
                    Sharpening filter;
                    filter.Process(image, 0, 0, 0);
                    break;
                }
                case FilterType::EdgeDetection: {
                    EdgeDetection filter;
                    filter.Process(image, 0, 0, param.DoubleParam);
                    break;
                }
                case FilterType::GaussianBlur: {
                    GaussianBlur filter;
                    filter.Process(image, 0, 0, param.DoubleParam);
                    break;
                }
                case FilterType::Crystallize: {
                    Crystallize filter;
                    filter.Process(image, param.IntParam1, 0, 0);
                    break;
                }
            }
        }

        image.Write(cmd_params.OutputFilePath);

    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
