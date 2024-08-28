#include "negative_filter.h"

void Negative::Process(Image &image, int64_t int_param1, int64_t int_param2, double double_param) {
    Pixels pixels = image.GetPixels();

    const uint8_t max_char = 255;

    for (auto &line : pixels) {
        for (auto &pixel : line) {
            pixel.Blue = max_char - pixel.Blue;
            pixel.Green = max_char - pixel.Green;
            pixel.Red = max_char - pixel.Red;
        }
    }

    image.SetPixels(pixels);
}
