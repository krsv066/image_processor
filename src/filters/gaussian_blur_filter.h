#include "abstract_filter.h"

namespace image_processor
{

class GaussianBlur final : public AbstractFilter
{
public:
    void Process(Image & image, int64_t int_param1, int64_t int_param2, double double_param) override;

private:
    std::vector<double> CalculateCoefficient(double sigma, int64_t delta_window);
    void ProcessLines(Image & image, const std::vector<double> & coefficients, double coefficients_sum, int64_t delta_window);
    void ProcessColumns(Image & image, const std::vector<double> & coefficients, double coefficients_sum, int64_t delta_window);
};

} // namespace image_processor
