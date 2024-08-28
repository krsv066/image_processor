#include "crop_filter.h"
#include <algorithm>

void Crop::Process(Image &image, int64_t int_param1, int64_t int_param2, double double_param) {
    Pixels pixels = image.GetPixels();
    int32_t new_width = std::min(static_cast<int32_t>(int_param1), image.GetWidth());
    int32_t new_height = std::min(static_cast<int32_t>(int_param1), image.GetHeight());

    image.SetWidth(new_width);
    image.SetHeight(new_height);

    std::reverse(pixels.begin(), pixels.end());
    pixels.resize(new_height);
    for (auto &line : pixels) {
        line.resize(new_width);
    }
    std::reverse(pixels.begin(), pixels.end());

    image.SetPixels(pixels);
}
