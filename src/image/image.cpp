#include "image.h"
#include <fstream>

Image::Image(const char *input_file_path) {
    Read(input_file_path);
}

void Image::Read(const char *input_file_path) {
    std::ifstream input(input_file_path, std::ios_base::binary);
    if (!input) {
        throw std::runtime_error("Unable to open the input file.");
    }

    input.read(reinterpret_cast<char *>(&header_), sizeof(header_));
    const uint16_t valid_file_format = 0x4D42;
    if (header_.file_type != valid_file_format) {
        throw std::runtime_error("Unrecognized file format.");
    }

    input.read(reinterpret_cast<char *>(&info_header_), sizeof(info_header_));
    const uint16_t valid_bits = 24;
    if (info_header_.bits != valid_bits) {
        throw std::runtime_error("Unrecognized file format. Only 24 bits allowed.");
    }

    input.seekg(header_.offset_data, input.beg);

    const uint32_t offset = CountOffset();

    for (size_t i = 0; i < info_header_.height; ++i) {
        std::vector<Pixel> line;
        for (size_t j = 0; j < info_header_.width; ++j) {
            Pixel pixel;
            input.read(reinterpret_cast<char *>(&pixel), sizeof(pixel));
            line.push_back(pixel);
        }
        pixels_.push_back(line);
        input.seekg(offset, input.cur);
    }
}

void Image::Write(const char *output_file_path) {
    std::ofstream output(output_file_path, std::ios_base::binary);
    if (!output) {
        throw std::runtime_error("Unable to open the output image file.");
    }

    output.write(reinterpret_cast<const char *>(&header_), sizeof(header_));
    output.write(reinterpret_cast<const char *>(&info_header_), sizeof(info_header_));

    const uint32_t offset = CountOffset();

    for (const auto &line : pixels_) {
        output.write(reinterpret_cast<const char *>(line.data()), info_header_.width * 3);
        std::vector<uint8_t> offset_vector(offset, 0);
        output.write(reinterpret_cast<const char *>(offset_vector.data()), offset);
    }
}

Pixels Image::GetPixels() const {
    return pixels_;
}

void Image::SetPixels(const Pixels &pixels) {
    pixels_ = pixels;
}

int32_t Image::GetWidth() const {
    return info_header_.width;
}

void Image::SetWidth(int32_t new_width) {
    info_header_.width = new_width;
}

int32_t Image::GetHeight() const {
    return info_header_.height;
}

void Image::SetHeight(int32_t new_height) {
    info_header_.height = new_height;
}

uint32_t Image::CountOffset() const {
    return (4 - info_header_.width * 3 % 4) % 4;
}
