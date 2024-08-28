#include "edge_detection_filter.h"
#include "scale_filter.h"
#include "grayscale_filter.h"
#include <algorithm>

void EdgeDetection::Process(Image &image, int64_t int_param1, int64_t int_param2, double double_param) {
    Grayscale grayscale_filter;
    grayscale_filter.Process(image, 0, 0, 0);

    ScaleFilter scale_filter;
    const int64_t scale = 4;
    scale_filter.Process(image, scale, 0, 0);

    Pixels pixels = image.GetPixels();

    const uint8_t min_char = 0;
    const uint8_t max_char = 255;

    const uint8_t threshold =
        std::clamp(static_cast<uint8_t>(double_param * static_cast<double>(max_char)), min_char, max_char);

    for (auto &line : pixels) {
        for (auto &pixel : line) {
            if (pixel.Blue > threshold || pixel.Green > threshold || pixel.Red > threshold) {
                pixel.Blue = max_char;
                pixel.Green = max_char;
                pixel.Red = max_char;
            } else {
                pixel.Blue = min_char;
                pixel.Green = min_char;
                pixel.Red = min_char;
            }
        }
    }

    image.SetPixels(pixels);
}
