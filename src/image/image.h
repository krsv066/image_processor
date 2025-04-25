#pragma once

#include <cstdint>
#include <vector>

namespace image_processor
{

#pragma pack(push, 1)

struct Header
{
    uint16_t file_type;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset_data;
};

struct InfoHeader
{
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
};

struct Pixel
{
    uint8_t Blue = 0;
    uint8_t Green = 0;
    uint8_t Red = 0;
};

#pragma pack(pop)

using Pixels = std::vector<std::vector<Pixel>>;

class Image
{
public:
    explicit Image(const char * input_file_path);
    explicit Image(const Header & header, const InfoHeader & info_header, const Pixels & pixels);
    void Read(const char * input_file_path);
    void Write(const char * output_file_path);
    Pixels GetPixels() const;
    void SetPixels(const Pixels & pixels);
    int32_t GetWidth() const;
    void SetWidth(int32_t new_width);
    int32_t GetHeight() const;
    void SetHeight(int32_t new_height);
    uint32_t CountOffset() const;

private:
    Header header_;
    InfoHeader info_header_;
    Pixels pixels_;
};

} // namespace image_processor
