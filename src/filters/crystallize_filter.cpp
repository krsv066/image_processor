#include "crystallize_filter.h"
#include <cmath>

std::vector<std::pair<int32_t, int32_t>> Crystallize::RandomCoords(const int32_t crystals_count, const int32_t height,
                                                                   const int32_t width) {
    std::vector<std::pair<int32_t, int32_t>> numbers;
    for (size_t i = 0; i < crystals_count; ++i) {
        numbers.emplace_back(
            std::make_pair(static_cast<int32_t>(std::rand()) % height, static_cast<int32_t>(std::rand()) % width));
    }
    return numbers;
}

int32_t Crystallize::FindNearestPixel(const std::vector<std::pair<int32_t, int32_t>> &random_coords,
                                      const std::pair<int32_t, int32_t> &coords) {
    double best_distance = static_cast<double>(UINT32_MAX);
    int32_t best_pixel_number = 0;
    for (int32_t i = 0; i < random_coords.size(); ++i) {
        double distance =
            std::sqrt((coords.first - random_coords[i].first) * (coords.first - random_coords[i].first) +
                      (coords.second - random_coords[i].second) * (coords.second - random_coords[i].second));

        if (distance < best_distance) {
            best_distance = distance;
            best_pixel_number = i;
        }
    }

    return best_pixel_number;
}

void Crystallize::Process(Image &image, int64_t int_param1, int64_t int_param2, double double_param) {
    Pixels pixels = image.GetPixels();

    const int32_t crystals_count = static_cast<int32_t>(int_param1);
    std::vector<std::pair<int32_t, int32_t>> random_coords =
        RandomCoords(crystals_count, image.GetHeight(), image.GetWidth());

    std::vector<Pixel> random_pixels_colors;
    for (size_t i = 0; i < crystals_count; ++i) {
        random_pixels_colors.push_back(pixels[random_coords[i].first][random_coords[i].second]);
    }

    std::vector<Pixel> new_pixels_line(image.GetHeight(), {0, 0, 0});
    std::vector<std::vector<Pixel>> new_pixels(image.GetHeight(), new_pixels_line);

    for (size_t line_num = 0; line_num < image.GetHeight(); ++line_num) {
        for (size_t column_num = 0; column_num < image.GetWidth(); ++column_num) {
            int32_t number = FindNearestPixel(random_coords, std::pair<int32_t, int32_t>{line_num, column_num});
            new_pixels[line_num][column_num] = random_pixels_colors[number];
        }
    }

    image.SetPixels(new_pixels);
}
