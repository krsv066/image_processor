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
    CmdParams cmd_params_;
};

} // namespace image_processor
