#include "sharpening_filter.h"
#include "scale_filter.h"

namespace image_processor
{

void Sharpening::Process(Image & image, int64_t int_param1, int64_t int_param2, double double_param)
{
    ScaleFilter filter;
    const int64_t scale = 5;
    filter.Process(image, scale, 0, 0);
}

} // namespace image_processor
