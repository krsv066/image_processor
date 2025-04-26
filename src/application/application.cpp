#include "application.h"
#include "concrete_filter_factory.h"
#include "filter_factory.h"
#include "image.h"

#include <iostream>
#include <memory>

namespace image_processor
{

Application::Application(int argc, char * argv[])
    : cmd_params_(Parser::Parse(argc, argv))
{
}

void Application::Run() const
{
    std::vector<FilterParamsWithType> params = cmd_params_.filters_params;

    Image image(cmd_params_.input_path);
    std::unique_ptr<FilterFactory> factory = std::make_unique<ConcreteFilterFactory>();

    for (const auto & param : params)
    {
        std::unique_ptr<AbstractFilter> filter = factory->CreateFilter(param.type);

        if (filter)
        {
            filter->Process(image, {param.int_param1, param.int_param2, param.double_param});
        }
        else
        {
            std::cerr << "Failed to create filter of specified type" << std::endl;
        }
    }

    image.Write(cmd_params_.output_path);
}

} // namespace image_processor
