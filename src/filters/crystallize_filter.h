#include "abstract_filter.h"

namespace image_processor
{

class Crystallize : AbstractFilter
{
public:
    void Process(Image & image, int64_t int_param1, int64_t int_param2, double double_param) override;

private:
    std::vector<std::pair<int32_t, int32_t>> RandomCoords(int32_t crystals_count, int32_t height, int32_t width);
    int32_t FindNearestPixel(const std::vector<std::pair<int32_t, int32_t>> & random_coords, const std::pair<int32_t, int32_t> & coords);
};

} // namespace image_processor
