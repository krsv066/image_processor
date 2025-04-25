#include "negative_filter.h"
#include <cstdint>
#include <limits>

namespace image_processor
{

void Negative::Process(Image & image, int64_t int_param1, int64_t int_param2, double double_param)
{
    Pixels pixels = image.GetPixels();

    for (auto & line : pixels)
    {
        for (auto & pixel : line)
        {
            pixel.Blue = std::numeric_limits<uint8_t>::max() - pixel.Blue;
            pixel.Green = std::numeric_limits<uint8_t>::max() - pixel.Green;
            pixel.Red = std::numeric_limits<uint8_t>::max() - pixel.Red;
        }
    }

    image.SetPixels(pixels);
}

} // namespace image_processor
