#include "abstract_filter.h"

namespace image_processor
{

class Crystallize final : public AbstractFilter
{
public:
    void Process(Image & image, FilterParams params) override;

private:
    std::vector<std::pair<int32_t, int32_t>> RandomCoords(int32_t crystals_count, int32_t height, int32_t width);
    int32_t FindNearestPixel(const std::vector<std::pair<int32_t, int32_t>> & random_coords, const std::pair<int32_t, int32_t> & coords);
};

} // namespace image_processor
