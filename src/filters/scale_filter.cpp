#include "scale_filter.h"
#include <algorithm>

void ScaleFilter::Process(Image &image, int64_t int_param1, int64_t int_param2, double double_param) {
    Pixels pixels = image.GetPixels();
    std::vector<Pixel> new_pixels_line(image.GetWidth(), {0, 0, 0});
    std::vector<std::vector<Pixel>> new_pixels(image.GetHeight(), new_pixels_line);

    const int64_t min_char = 0;
    const int64_t max_char = 255;

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Pixel new_pixel;
            int64_t new_blue = static_cast<int64_t>(pixels[i][j].Blue) * int_param1;
            int64_t new_green = static_cast<int64_t>(pixels[i][j].Green) * int_param1;
            int64_t new_red = static_cast<int64_t>(pixels[i][j].Red) * int_param1;

            uint8_t extreme_count = 0;

            if (i > 0) {
                new_blue -= static_cast<int64_t>(pixels[i - 1][j].Blue);
                new_green -= static_cast<int64_t>(pixels[i - 1][j].Green);
                new_red -= static_cast<int64_t>(pixels[i - 1][j].Red);
            } else {
                ++extreme_count;
            }

            if (j > 0) {
                new_blue -= static_cast<int64_t>(pixels[i][j - 1].Blue);
                new_green -= static_cast<int64_t>(pixels[i][j - 1].Green);
                new_red -= static_cast<int64_t>(pixels[i][j - 1].Red);
            } else {
                ++extreme_count;
            }

            if (i < image.GetHeight() - 1) {
                new_blue -= static_cast<int64_t>(pixels[i + 1][j].Blue);
                new_green -= static_cast<int64_t>(pixels[i + 1][j].Green);
                new_red -= static_cast<int64_t>(pixels[i + 1][j].Red);
            } else {
                ++extreme_count;
            }

            if (j < image.GetWidth() - 1) {
                new_blue -= static_cast<int64_t>(pixels[i][j + 1].Blue);
                new_green -= static_cast<int64_t>(pixels[i][j + 1].Green);
                new_red -= static_cast<int64_t>(pixels[i][j + 1].Red);
            } else {
                ++extreme_count;
            }

            for (uint8_t k = 0; k < extreme_count; ++k) {
                new_blue -= static_cast<int64_t>(pixels[i][j].Blue);
                new_green -= static_cast<int64_t>(pixels[i][j].Green);
                new_red -= static_cast<int64_t>(pixels[i][j].Red);
            }

            new_pixel.Blue = static_cast<uint8_t>(std::clamp(new_blue, min_char, max_char));
            new_pixel.Green = static_cast<uint8_t>(std::clamp(new_green, min_char, max_char));
            new_pixel.Red = static_cast<uint8_t>(std::clamp(new_red, min_char, max_char));
            new_pixels[i][j] = new_pixel;
        }
    }

    image.SetPixels(new_pixels);
}
