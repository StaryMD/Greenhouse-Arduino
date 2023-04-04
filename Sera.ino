// Makes the code runnable on tinkercad
//   meaning disables the database and replaces DHT11 with tinkercad's senzor
#define _TINKERCAD_ false

// Activates the database uploading code
#define _USE_DATABASE_ true

#include "Melody.h"
#include "LedRGB.h"

constexpr float kTemperatureAcceptableMin = 25.20f;
constexpr float kTemperatureAcceptableMax = 25.40f;

constexpr uint8_t kPinButton = 2;

constexpr uint8_t kPinLedExteriorR = 3;
constexpr uint8_t kPinLedExteriorB = 4;
constexpr uint8_t kPinLedExteriorG = 5;

constexpr uint8_t kPinLedInteriorR = 6;
constexpr uint8_t kPinLedInteriorB = 7;
constexpr uint8_t kPinLedInteriorG = 8;

constexpr uint8_t kPinLedOnOff = 9;
constexpr uint8_t kPinPiezo = 10;

constexpr uint8_t kPinTemperatureExterior = 11;
constexpr uint8_t kPinTemperatureInterior = 12;

#if !_TINKERCAD_

#include "DHT.h"

constexpr uint8_t CELSIUS = 0;
constexpr uint8_t FARENHEIT = 1;

DHT dht_exterior(kPinTemperatureExterior, DHT11);
DHT dht_interior(kPinTemperatureInterior, DHT11);

#endif /* !_TINKERCAD_ */

#if _USE_DATABASE_ && !_TINKERCAD_

#include "mysql.h"

mysql::DatabaseConnection connection("localhost", "root", "root", "proiect_si");

constexpr unsigned long kUploadInterval = 2000; // in ms
unsigned long time_of_last_upload = 0;

#endif /* _USE_DATABASE_ && !_TINKERCAD_ */

enum TempState {
  NORMAL,
  COLD,
  WARM,
};

enum SystemState {
  OFF,
  ON,
};

uint8_t TemperatureCompare(const float temperature) {
  if (temperature < kTemperatureAcceptableMin) {
    return COLD;
  } else if (temperature < kTemperatureAcceptableMax) {
    return NORMAL;
  } else {
    return WARM;
  }
}

LedRGB led_exterior(kPinLedExteriorR, kPinLedExteriorG, kPinLedExteriorB);
LedRGB led_interior(kPinLedInteriorR, kPinLedInteriorG, kPinLedInteriorB);

SystemState system_state = OFF;

/**
 * @brief Called by the iterrupt on the pin **kPinButton**.
 * 
 */
void buttonPressEvent() {
  static bool is_even = true;

  if (is_even) {
    if (system_state == OFF) {
      system_state = ON;
    } else {
      system_state = OFF;
    }
  }
  is_even = !is_even;
}

Melody1 melody1(kPinPiezo);
Melody2 melody2(kPinPiezo);

void setup() {
  pinMode(kPinButton, INPUT);
  pinMode(kPinLedOnOff, OUTPUT);

  attachInterrupt(
    digitalPinToInterrupt(kPinButton),
    buttonPressEvent, CHANGE
  );

  Serial.begin(9600);

#if !_TINKERCAD_

  dht_exterior.begin();
  dht_interior.begin();

#endif /* !_TINKERCAD_ */

#if _USE_DATABASE_ && !_TINKERCAD_

  connection.Connect();

  if (connection.get_error_code() != mysql::kSuccess) {
    Serial.println(F("DB Connection failed"));
  }

#endif /* _USE_DATABASE_ && !_TINKERCAD_ */
}

void loop() {
  // Keep the previous states to know wheter to reset the melody or not, melody only resets when the state changes
  static uint8_t prev_state_interior = NORMAL;
  static uint8_t prev_state_exterior = NORMAL;

  switch (system_state) {
    case ON: {
      digitalWrite(kPinLedOnOff, LOW);

#if _TINKERCAD_
      const int temperature_exterior_read = analogRead(kPinTemperatureExterior);
      const int temperature_interior_read = analogRead(kPinTemperatureInterior);

      const float temperature_exterior_value = map(temperature_exterior_read, 20, 358, -40, 125);
      const float temperature_interior_value = map(temperature_interior_read, 20, 358, -40, 125);

      Serial.print(F("Ext t: ")); Serial.println(temperature_exterior_value, 2);
      Serial.print(F("Int t: ")); Serial.println(temperature_interior_value, 2);
#else /* _TINKERCAD_ */

      // Read the values from the two senzors
      const float temperature_exterior_value = dht_exterior.readTemperature(CELSIUS);
      const float humidity_exterior_value = dht_exterior.readHumidity();
      const float temperature_interior_value = dht_interior.readTemperature(CELSIUS);
      const float humidity_interior_value = dht_interior.readHumidity();

      Serial.print(F("Ext t: ")); Serial.print(temperature_exterior_value, 2);
      Serial.print(F("  h: ")); Serial.print(humidity_exterior_value, 2);
      Serial.print(F("  Int t: ")); Serial.print(temperature_interior_value, 2);
      Serial.print(F("  h: ")); Serial.println(humidity_interior_value, 2);
#endif /* _TINKERCAD_ */

#if _USE_DATABASE_ && !_TINKERCAD_

      // Only upload the data to the database once every **kUploadInterval** milliseconds
      if (millis() - time_of_last_upload >= kUploadInterval) {
        time_of_last_upload = millis();
        
        // Call the query to insert the values of the EXTERIOR senzor in the database
        connection.Query(
          "CALL insert_senzor_exterior(" +
          String(temperature_exterior_value, 2) + "," +
          String(humidity_exterior_value, 2) + ");"
        );

        // Call the query to insert the values of the INTERIOR senzor in the database
        connection.Query(
          "CALL insert_senzor_interior(" +
          String(temperature_interior_value, 2) + "," +
          String(humidity_interior_value, 2) + ");"
        );
      }

#endif /* _USE_DATABASE_ && !_TINKERCAD_ */
      // Save the current states dictated by the temperature
      const uint8_t current_state_interior = TemperatureCompare(temperature_interior_value);
      const uint8_t current_state_exterior = TemperatureCompare(temperature_exterior_value);

      // Control the exterior LED
      switch (current_state_exterior) {
        case NORMAL: {
          led_exterior.PaintGreen();
          break;
        }
        case COLD: {
          led_exterior.PaintBlue();
          break;
        }
        case WARM: {
          led_exterior.PaintRed();
          break;
        }
      }

      // Control the interior LED and the melody
      switch (current_state_interior) {
        case NORMAL: {
          led_interior.PaintGreen();
          break;
        }
        case COLD: {
          led_interior.PaintBlue();

          // Reset the melody if state has changed to this one
          if (current_state_exterior != prev_state_exterior) {
            melody2.Reset();
          }

          // Play the next note of Harry Potter OST
          if (melody2.IsTimeForNextNote()) {
            melody2.PlayNote();
          }
          break;
        }
        case WARM: {
          led_interior.PaintRed();

          // Reset the melody if state has changed to this one
          if (current_state_exterior != prev_state_exterior) {
            melody1.Reset();
          }

          // Play the next note of Pirates of the Caribbean
          if (melody1.IsTimeForNextNote()) {
            melody1.PlayNote();
          }
          break;
        }
      }

      prev_state_exterior = current_state_exterior;
      prev_state_interior = current_state_interior;

      delay(20);
      break;
    }
    case OFF: {
      // Keep the number of the last second to know when it changes
      static long last_second = -1;
      digitalWrite(kPinLedOnOff, HIGH);

      // Beacuse the message is repetitive and may lead to confusion,
      //     print the total runtime in seconds as well
      if (Serial && millis() / 1000 != last_second) {
        last_second = millis() / 1000;
        Serial.print(F("Oprit  "));
        Serial.println(millis() / 1000);
      }

      // Turn off the LEDS
      led_interior.NoColor();
      led_exterior.NoColor();

      delay(100);
      break;
    }
  }

}
