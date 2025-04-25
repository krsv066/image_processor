#include "concrete_filter_factory.h"
#include "filter_factory.h"
#include "image.h"
#include "parser.h"

#include <iostream>

int main(int argc, char * argv[])
{
    image_processor::CmdParams cmd_params = image_processor::Parser::Parse(argc, argv);
    std::vector<image_processor::FilterParams> params = cmd_params.FiltersParams;

    try
    {
        image_processor::Image image(cmd_params.InputFilePath);
        std::unique_ptr<image_processor::FilterFactory> factory = std::make_unique<image_processor::ConcreteFilterFactory>();

        for (const auto & param : params)
        {
            std::unique_ptr<image_processor::AbstractFilter> filter = factory->CreateFilter(param.Filter);

            if (filter)
            {
                filter->Process(image, param.IntParam1, param.IntParam2, param.DoubleParam);
            }
            else
            {
                std::cerr << "Failed to create filter of specified type" << std::endl;
            }
        }

        image.Write(cmd_params.OutputFilePath);
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
