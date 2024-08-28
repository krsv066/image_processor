#include "gaussian_blur_filter.h"
#include <algorithm>
#include <cmath>

std::vector<double> GaussianBlur::CalculateCoefficient(const double sigma, const int64_t delta_window) {
    const int64_t window_size = delta_window * 2 + 1;
    std::vector<double> coefficients;
    coefficients.reserve(window_size);

    for (int64_t i = 0; i < window_size; ++i) {
        coefficients.push_back(std::exp(
            -(static_cast<double>(i - delta_window) * static_cast<double>(i - delta_window)) / (2 * (sigma * sigma))));
    }

    return coefficients;
}

double GaussianBlur::CalculateSum(const std::vector<double> &coefficients) {
    double sum_res = 0;
    for (auto i : coefficients) {
        sum_res += i;
    }
    return sum_res;
}

void GaussianBlur::ProcessLines(Image &image, const std::vector<double> &coefficients, double coefficients_sum,
                                const int64_t delta_window) {
    Pixels pixels = image.GetPixels();
    std::vector<Pixel> new_pixels_line(image.GetHeight(), {0, 0, 0});
    std::vector<std::vector<Pixel>> new_pixels(image.GetHeight(), new_pixels_line);

    for (int64_t line = 0; line < image.GetHeight(); ++line) {
        for (int64_t x_0 = 0; x_0 < image.GetWidth(); ++x_0) {
            double new_blue = 0;
            double new_green = 0;
            double new_red = 0;

            for (int64_t x = x_0 - delta_window; x <= x_0 + delta_window; ++x) {
                int64_t curr_x_0 = std::clamp(x, static_cast<int64_t>(0), static_cast<int64_t>(image.GetWidth() - 1));
                new_blue += static_cast<double>(pixels[line][curr_x_0].Blue) * coefficients[x - (x_0 - delta_window)];
                new_green += static_cast<double>(pixels[line][curr_x_0].Green) * coefficients[x - (x_0 - delta_window)];
                new_red += static_cast<double>(pixels[line][curr_x_0].Red) * coefficients[x - (x_0 - delta_window)];
            }

            new_blue = new_blue / coefficients_sum;
            new_green = new_green / coefficients_sum;
            new_red = new_red / coefficients_sum;

            Pixel new_pixel{static_cast<uint8_t>(new_blue), static_cast<uint8_t>(new_green),
                            static_cast<uint8_t>(new_red)};
            new_pixels[line][x_0] = new_pixel;
        }
    }
    image.SetPixels(new_pixels);
}

void GaussianBlur::ProcessColumns(Image &image, const std::vector<double> &coefficients, double coefficients_sum,
                                  const int64_t delta_window) {
    Pixels pixels = image.GetPixels();
    std::vector<Pixel> new_pixel_line(image.GetHeight(), {0, 0, 0});
    std::vector<std::vector<Pixel>> new_pixels(image.GetHeight(), new_pixel_line);

    for (int64_t column = 0; column < image.GetWidth(); ++column) {
        for (int64_t y_0 = 0; y_0 < image.GetHeight(); ++y_0) {
            double new_blue = 0;
            double new_green = 0;
            double new_red = 0;

            for (int64_t y = y_0 - delta_window; y <= y_0 + delta_window; ++y) {
                int64_t curr_y_0 = std::clamp(y, static_cast<int64_t>(0), static_cast<int64_t>(image.GetHeight() - 1));
                new_blue += static_cast<double>(pixels[curr_y_0][column].Blue) * coefficients[y - (y_0 - delta_window)];
                new_green +=
                    static_cast<double>(pixels[curr_y_0][column].Green) * coefficients[y - (y_0 - delta_window)];
                new_red += static_cast<double>(pixels[curr_y_0][column].Red) * coefficients[y - (y_0 - delta_window)];
            }

            new_blue = new_blue / coefficients_sum;
            new_green = new_green / coefficients_sum;
            new_red = new_red / coefficients_sum;

            Pixel new_pixel{static_cast<uint8_t>(new_blue), static_cast<uint8_t>(new_green),
                            static_cast<uint8_t>(new_red)};
            new_pixels[y_0][column] = new_pixel;
        }
    }
    image.SetPixels(new_pixels);
}

void GaussianBlur::Process(Image &image, int64_t int_param1, int64_t int_param2, double double_param) {
    const double sigma = double_param;
    const int64_t sigma_ceil = std::ceil(sigma);
    const int64_t delta_window = 3 * sigma_ceil;

    const std::vector<double> coefficients = CalculateCoefficient(sigma, delta_window);
    double coefficients_sum = CalculateSum(coefficients);

    ProcessLines(image, coefficients, coefficients_sum, delta_window);
    ProcessColumns(image, coefficients, coefficients_sum, delta_window);
}
