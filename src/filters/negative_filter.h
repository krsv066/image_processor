#include "abstract_filter.h"

namespace image_processor
{

class Negative : AbstractFilter
{
public:
    void Process(Image & image, int64_t int_param1, int64_t int_param2, double double_param) override;
};

} // namespace image_processor
