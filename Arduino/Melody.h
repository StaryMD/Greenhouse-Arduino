#ifndef MELODY_H
#define MELODY_H

#include "Arduino.h"
#include "pitches.h"

class Melody {
 public:
  Melody() = delete;

  /**
   * @brief Initilizes the pin for the Pizeo buzzer.
   * 
   * @param pin Pin of the buzzer.
   */
  Melody(const uint8_t pin);

  /**
   * @brief Resets the melody.
   * 
   */
  void Reset();

 protected:
  // Map the 16 pitches used in the melody to vales 0-16 for compression
  const int map_note_to_piezo[16] = {
    0, 262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988, 466
  };

  const uint8_t pin_piezo;

  long ms_of_last_note = 0;
  int current_note_index = 0;
};

class Melody1 : public Melody {
 public:
  Melody1() = delete;

  /**
   * @brief Initilizes the pin for the Pizeo buzzer.
   * 
   * @param pin Pin of the buzzer.
   */
  Melody1(const uint8_t pin);

  /**
   * @brief Checks if it's time for the next note.
   * 
   * @return bool Whether it's time for the next note.
   */
  bool IsTimeForNextNote();

  /**
   * @brief Plays the next note.
   * 
   */
  void PlayNote();

  /**
   * @brief Get the duration a certain note.
   * 
   * @param index Index of note.
   * @return int Duration of note.
   */
  int get_duration(const int index) const;

 private:
  /**
   * @brief Store 4 two-bit values in a unsigned byte
   * 
   */
  class MyByte {
   public:
    /**
     * @brief Initializes the bitfields with the given bits.
     * 
     * @param val Bits to initialize with.
     */
    MyByte(const uint8_t val);

    /**
     * @brief Get one of the 4 numbers stored.
     * 
     * @param index Pozition 0-3 of the bits
     * @return uint8_t The bits.
     */
    uint8_t get_field(const int index) const;

   private:
    uint8_t a0 : 2;
    uint8_t a1 : 2;
    uint8_t a2 : 2;
    uint8_t a3 : 2;

  };

  static constexpr float melody_speed = 1.0f;
  static constexpr int note_count = 203;

  const uint8_t notes[note_count] = {
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
    NOTE_A4, NOTE_G4, NOTE_A4, REST,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
    NOTE_A4, NOTE_G4, NOTE_A4, REST,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, REST,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, REST,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, REST,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
    NOTE_D5, NOTE_E5, NOTE_A4, REST,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, REST,
    NOTE_C5, NOTE_A4, NOTE_B4, REST,

    NOTE_A4, NOTE_A4,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
    NOTE_A4, NOTE_G4, NOTE_A4, REST,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
    NOTE_A4, NOTE_G4, NOTE_A4, REST,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, REST,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, REST,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, REST,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
    NOTE_D5, NOTE_E5, NOTE_A4, REST,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, REST,
    NOTE_C5, NOTE_A4, NOTE_B4, REST,

    NOTE_E5, REST, REST, NOTE_F5, REST, REST,
    NOTE_E5, NOTE_E5, REST, NOTE_G5, REST, NOTE_E5, NOTE_D5, REST, REST,
    NOTE_D5, REST, REST, NOTE_C5, REST, REST,
    NOTE_B4, NOTE_C5, REST, NOTE_B4, REST, NOTE_A4,

    NOTE_E5, REST, REST, NOTE_F5, REST, REST,
    NOTE_E5, NOTE_E5, REST, NOTE_G5, REST, NOTE_E5, NOTE_D5, REST, REST,
    NOTE_D5, REST, REST, NOTE_C5, REST, REST,
    NOTE_B4, NOTE_C5, REST, NOTE_B4, REST, NOTE_A4
  };

  /**
   * @brief Array of durations; 4 times smaller than the note_count because it's compressed 4 times.
   * 
   * @details Values are compressed so: 4 values, initially 8 bits with 6 not used, becam 2 bits and
   * are stored 4 in one byte
   */
  const MyByte durations[51] = {
    MyByte(191), MyByte(255), MyByte(255), MyByte(254), MyByte(235), MyByte(235), MyByte(191), MyByte(255), MyByte(255), MyByte(254), MyByte(254), MyByte(235),
    MyByte(191), MyByte(255), MyByte(254), MyByte(254), MyByte(235), MyByte(235), MyByte(191), MyByte(254), MyByte(254), MyByte(235), MyByte(191), MyByte(191),
    MyByte(255), MyByte(255), MyByte(254), MyByte(235), MyByte(235), MyByte(191), MyByte(255), MyByte(255), MyByte(235), MyByte(235), MyByte(190), MyByte(191),
    MyByte(255), MyByte(234), MyByte(190), MyByte(255), MyByte(255), MyByte(190), MyByte(235), MyByte(255), MyByte(190), MyByte(235), MyByte(255), MyByte(191),
    MyByte(171), MyByte(254), MyByte(127)
  };

};

class Melody2 : public Melody {
 public:
  Melody2() = delete;

  /**
   * @brief Initilizes the pin for the Pizeo buzzer.
   * 
   * @param pin Pin of the buzzer.
   */
  Melody2(const uint8_t pin);

  /**
   * @brief Checks if it's time for the next note.
   * 
   * @return bool Whether it's time for the next note.
   */
  bool IsTimeForNextNote();

  /**
   * @brief Plays the next note.
   * 
   */
  void PlayNote();

 private:
  static constexpr float melody_speed = 1.0f;
  static constexpr int note_count = 62;

  const uint8_t notes[note_count] = {
    REST, NOTE_D4,
    NOTE_G4, NOTE_AS4, NOTE_A4,
    NOTE_G4, NOTE_D5,
    NOTE_C5,
    NOTE_A4,
    NOTE_G4, NOTE_AS4, NOTE_A4,
    NOTE_F4, NOTE_GS4,
    NOTE_D4,
    NOTE_D4,

    NOTE_G4, NOTE_AS4, NOTE_A4,
    NOTE_G4, NOTE_D5,
    NOTE_F5, NOTE_E5,
    NOTE_DS5, NOTE_B4,
    NOTE_DS5, NOTE_D5, NOTE_CS5,
    NOTE_CS4, NOTE_B4,
    NOTE_G4,
    NOTE_AS4,

    NOTE_D5, NOTE_AS4,
    NOTE_D5, NOTE_AS4,
    NOTE_DS5, NOTE_D5,
    NOTE_CS5, NOTE_A4,
    NOTE_AS4, NOTE_D5, NOTE_CS5,
    NOTE_CS4, NOTE_D4,
    NOTE_D5,
    REST, NOTE_AS4,

    NOTE_D5, NOTE_AS4,
    NOTE_D5, NOTE_AS4,
    NOTE_F5, NOTE_E5,
    NOTE_DS5, NOTE_B4,
    NOTE_DS5, NOTE_D5, NOTE_CS5,
    NOTE_CS4, NOTE_AS4,
    NOTE_G4
  };

  const uint8_t durations[note_count] = {
    2, 4,
    4, 8, 4,
    2, 4,
    2,
    2,
    4, 8, 4,
    2, 4,
    1,
    4,

    4, 8, 4,
    2, 4,
    2, 4,
    2, 4,
    4, 8, 4,
    2, 4,
    1,
    4,

    2, 4,
    2, 4,
    2, 4,
    2, 4,
    4, 8, 4,
    2, 4,
    1,
    4, 4,

    2, 4,
    2, 4,
    2, 4,
    2, 4,
    4, 8, 4,
    2, 4,
    1
  };
};


#endif /* MELODY_H */
