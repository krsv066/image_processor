#pragma once

#include <cstdint>
#include <iostream>
#include <vector>

#pragma pack(push, 1)

struct Header {
    uint16_t file_type;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset_data;

    bool operator==(const Header &) const = default;
};

struct InfoHeader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t n_colours;
    uint32_t important_colours;

    bool operator==(const InfoHeader &) const = default;
};

struct Pixel {
    Pixel(uint8_t blue, uint8_t green, uint8_t red) : Blue(blue), Green(green), Red(red){};

    Pixel() : Pixel(0, 0, 0){};

    uint8_t Blue;
    uint8_t Green;
    uint8_t Red;

    bool operator==(const Pixel &) const = default;
};

#pragma pack(pop)

using Pixels = std::vector<std::vector<Pixel>>;

class Image {
public:
    explicit Image(const char *input_file_path);

    explicit Image(const Header &header, const InfoHeader &info_header, const Pixels &pixels)
        : header_(header), info_header_(info_header), pixels_(pixels){};

    void Read(const char *input_file_path);

    void Write(const char *output_file_path);

    Pixels GetPixels() const;

    void SetPixels(const Pixels &pixels);

    int32_t GetWidth() const;

    void SetWidth(int32_t new_width);

    int32_t GetHeight() const;

    void SetHeight(int32_t new_height);

    uint32_t CountOffset() const;

    bool operator==(const Image &) const = default;

private:
    Header header_;
    InfoHeader info_header_;
    Pixels pixels_;
};
