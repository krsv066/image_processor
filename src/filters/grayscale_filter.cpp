#include "grayscale_filter.h"

void Grayscale::Process(Image &image, int64_t int_param1, int64_t int_param2, double double_param) {
    Pixels pixels = image.GetPixels();

    for (auto &line : pixels) {
        for (auto &pixel : line) {
            const double red_scale = 0.299;
            const double green_scale = 0.587;
            const double blue_scale = 0.114;

            double grayscale_pixel = red_scale * static_cast<double>(pixel.Red) +
                                     green_scale * static_cast<double>(pixel.Green) +
                                     blue_scale * static_cast<double>(pixel.Blue);

            pixel.Blue = static_cast<uint8_t>(grayscale_pixel);
            pixel.Green = static_cast<uint8_t>(grayscale_pixel);
            pixel.Red = static_cast<uint8_t>(grayscale_pixel);
        }
    }

    image.SetPixels(pixels);
}
