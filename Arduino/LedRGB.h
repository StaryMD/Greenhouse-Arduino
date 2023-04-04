#ifndef LEDRGB_H
#define LEDRGB_H

#include "Arduino.h"

class LedRGB {
public:
  /**
   * @brief Initilizes the pins.
   * 
   * @param pin_r Pin for color red.
   * @param pin_g Pin for color green.
   * @param pin_b Pin for color blue.
   */
  LedRGB(const int pin_r, const int pin_g, const int pin_b);

  /**
   * @brief Sets the light to red.
   * 
   */
  void PaintRed();

  /**
   * @brief Sets the light to green.
   * 
   */
  void PaintGreen();

  /**
   * @brief Sets the light to blue.
   * 
   */
  void PaintBlue();
  /**
   * @brief Kills the light.
   * 
   */
  void NoColor();

  /**
   * @brief Give a RGB value to the light.
   * 
   * @param red How much red.
   * @param green How much green.
   * @param blue How much blue.
   */
  void Update(const uint8_t red, const uint8_t green, const uint8_t blue);

private:
  const int pin_r_;
  const int pin_g_;
  const int pin_b_;
};

#endif /* LEDRGB_H */
