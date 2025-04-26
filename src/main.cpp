#include "application.h"

#include <iostream>

int main(int argc, char * argv[])
{
    try
    {
        image_processor::Application app(argc, argv);
        app.Run();
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Caught unknown exception" << std::endl;
    }

    return 0;
}
