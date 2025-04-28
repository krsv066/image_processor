#include "edge_detection_filter.h"
#include "grayscale_filter.h"
#include "scale_filter.h"

#include <algorithm>
#include <cstdint>

namespace image_processor
{

void EdgeDetection::Process(Image & image, FilterParams params)
{
    Grayscale grayscale_filter;
    grayscale_filter.Process(image, {0, 0, 0});

    ScaleFilter scale_filter;
    const int64_t scale = 4;
    scale_filter.Process(image, {scale, 0, 0});

    Pixels pixels = image.GetPixels();

    const uint8_t max_char = 255;

    const uint8_t threshold = std::clamp(static_cast<uint8_t>(params.double_param * static_cast<double>(max_char)), uint8_t{0}, max_char);

    for (auto & line : pixels)
    {
        for (auto & pixel : line)
        {
            if (pixel.Blue > threshold || pixel.Green > threshold || pixel.Red > threshold)
            {
                pixel = {max_char, max_char, max_char};
            }
            else
            {
                pixel = {};
            }
        }
    }

    image.SetPixels(pixels);
}

} // namespace image_processor
