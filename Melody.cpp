#include "Melody.h"

Melody::Melody(const uint8_t pin)
  : pin_piezo(pin) {
  pinMode(pin_piezo, OUTPUT);
}

void Melody::Reset() {
  current_note_index = 0;
}

Melody1::Melody1(const uint8_t pin) : Melody(pin) {}

bool Melody1::IsTimeForNextNote() {
  if (current_note_index == 0) {
    return true;
  }

  const int duration = get_duration(current_note_index - 1);
  return (millis() - ms_of_last_note) >= duration;
}

void Melody1::PlayNote() {
  ms_of_last_note = millis();
  const int note = map_note_to_piezo[notes[current_note_index]];

  if (note != 0) {
    const int duration = get_duration(current_note_index);
    tone(pin_piezo, note, duration * 0.9);
  } else {
    noTone(pin_piezo);
  }

  current_note_index = (current_note_index + 1) % note_count;
}

int Melody1::get_duration(const int index) const {
  static const uint8_t mapped_to_actual[4] = { 0, 2, 4, 8 };

  const uint8_t duration2 = durations[index / 4].get_field(index % 4);

  return 1000 / melody_speed / mapped_to_actual[duration2];
}

Melody1::MyByte::MyByte(const uint8_t val) {
  a0 = val % 4;
  a1 = val / 4 % 4;
  a2 = val / 16 % 4;
  a3 = val / 64;
}

uint8_t Melody1::MyByte::get_field(const int index) const {
  switch (index) {
    case 0: {
      return a0;
    }
    case 1: {
      return a1;
    }
    case 2: {
      return a2;
    }
    case 3: {
      return a3;
    }
  }
  return -1;
}

Melody2::Melody2(const uint8_t pin)
  : Melody(pin) {}

bool Melody2::IsTimeForNextNote() {
  if (current_note_index == 0) {
    return true;
  }

  const int duration = 1000 / melody_speed / durations[current_note_index - 1];
  return (millis() - ms_of_last_note) >= duration;
}

void Melody2::PlayNote() {
  ms_of_last_note = millis();
  const int note = map_note_to_piezo[notes[current_note_index]];

  if (note != 0) {
    const int duration = 1000 / melody_speed / durations[current_note_index];
    tone(pin_piezo, note, duration * 0.9);
  } else {
    noTone(pin_piezo);
  }

  current_note_index = (current_note_index + 1) % note_count;
}
