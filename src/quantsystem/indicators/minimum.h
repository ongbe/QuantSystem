/*
 * \copyright Copyright 2015 All Rights Reserved.
 * \license @{
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @}
 */

#ifndef QUANTSYSTEM_INDICATORS_MINIMUM_H_
#define QUANTSYSTEM_INDICATORS_MINIMUM_H_

#include <string>
using std::string;
#include "quantsystem/indicators/window_indicator.h"
#include "quantsystem/indicators/iread_only_window.h"
#include "quantsystem/indicators/indicator_data_point.h"
namespace quantsystem {
namespace indicators {
/**
 * Represents an indictor capable of tracking the minimum value
 * and how many periods ago it occurred.
 * @ingroup IndicatorsLayer
 */
class Minimum : public WindowIndicator<IndicatorDataPoint> {
 public:
  /**
   * Creates a new Minimum indicator with the specified period.
   * @param period The period over which to look back
   */
  explicit Minimum(int period);

  /**
   * Creates a new Minimum indicator with the specified period.
   * @param name The name of this indicator
   * @param period The period over which to look back
   */
  Minimum(const string& name, int period);

  /**
   * Resets this indicator to its initial state.
   */
  virtual void Reset();

  /**
   * Gets a flag indicating when this indicator is ready and fully initialized.
   */
  virtual bool is_ready() {
    return samples() >= period();
  }

  int periods_since_minimum() const {
    return periods_since_minimum_;
  }

 protected:
  /**
   * Computes the next value of this indicator from the given state.
   * @param input The input given to the indicator.
   * @return A new value for this indicator.
   */
  virtual double ComputeNextValue(
      IReadOnlyWindow<IndicatorDataPoint>* window,
      const IndicatorDataPoint& input);

 private:
  // The number of periods since the minimum value was encountered
  int periods_since_minimum_;

  void set_periods_since_minimum(int periods_since_minimum) {
    periods_since_minimum_ = periods_since_minimum;
  }
};

}  // namespace indicators
}  // namespace quantsystem
#endif  // QUANTSYSTEM_INDICATORS_MINIMUM_H_
