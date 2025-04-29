#pragma once

#include "parser.h"

namespace image_processor
{

class Application
{
public:
    Application(int argc, char * argv[]);
    void Run() const;

private:
    CmdArgs cmd_params_;
};

} // namespace image_processor
