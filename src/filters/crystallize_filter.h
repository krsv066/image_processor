#include "abstract_filter.h"
#include <set>

class Crystallize : AbstractFilter {
public:
    void Process(Image &image, int64_t int_param1, int64_t int_param2, double double_param) override;

private:
    std::vector<std::pair<int32_t, int32_t>> RandomCoords(const int32_t crystals_count, const int32_t height,
                                                          const int32_t width);

    int32_t FindNearestPixel(const std::vector<std::pair<int32_t, int32_t>> &random_coords,
                             const std::pair<int32_t, int32_t> &coords);
};
