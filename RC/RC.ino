#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "nvs_flash.h"    // Include this for NVS functions
#include <BleKeyboard.h>  // For Bluetooth Keyboard functionality
#include <Bounce2.h>      // For button debounce

// Configuration Bluetooth
#define DEVICE_NAME "RCntrl P.1"
#define DEVICE_MANUFACTURER "S.R.I."
#define BATTERY_LEVEL 69
//BleKeyboard bleKeyboard(DEVICE_NAME, DEVICE_MANUFACTURER, BATTERY_LEVEL);
BleKeyboard bleKeyboard;

// Pinouts
int Button1 = 18;
int Button2 = 19;
int Button3 = 25;
int Button4 = 26;


// Parameters
#define NUM_BUTTONS 4
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {Button1, Button2, Button3, Button4};
Bounce* buttons = new Bounce[NUM_BUTTONS];

// Global variables for timing
unsigned long pressStartTime[NUM_BUTTONS] = {0};    // Track when the button was pressed
unsigned long lastHoldActionTime[NUM_BUTTONS] = {0}; // Track the last execution time for hold actions (only for buttons 0 and 1)
const unsigned long holdThreshold = 500;           // Threshold for hold (in milliseconds)
const unsigned long repeatInterval = 200;          // Interval for repeated actions while holding (for buttons 0 and 1)



// Global Variables
bool toggle_mode = false;

// Change the Bluetooth device name based on mode
void Toggle_Name() {
  if (toggle_mode) {
    esp_ble_gap_set_device_name("RCntrl P.2");
    Serial.println("* Profile 2 activated *");
  } else {
    esp_ble_gap_set_device_name("RCntrl P.1");
    Serial.println("* Profile 1 activated *");
  }
}

// Device setup
void setup() {
  Serial.begin(115200);
  Serial.println("Starting Rally Controller...");

  // Initialize Bluetooth keyboard
  bleKeyboard.begin();
  Serial.println("Bluetooth keyboard ready!");

  // Configure buttons with pull-up resistors and debounce interval
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i].attach(BUTTON_PINS[i], INPUT_PULLUP);
    buttons[i].interval(100);  // Debounce interval
  }
  Serial.println("Rally Controller ready!");
}

// Main loop
void loop() {
  // Check if Button1 and Button4 are pressed together to change mode
  // if ((digitalRead(Button1) == LOW) && (digitalRead(Button4) == LOW)) {
  //   delay(5000);  // Wait 5 seconds
  //   if ((digitalRead(Button1) == LOW) && (digitalRead(Button4) == LOW)) {
  //     toggle_mode = !toggle_mode;  // Toggle mode
  //     Toggle_Name();               // Update Bluetooth name
  //     Serial.println("Mode changed!");
  //   }
  // }

  // Update the state of the buttons
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i].update();
  }

  // Perform actions based on the current profile
  if (!toggle_mode) {
    handleProfile1();
  } else {
    handleProfile2();
  }
  //delay(50);
}

void handleProfile1() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    // Button pressed (start timing)
    if (buttons[i].fell()) {
      pressStartTime[i] = millis();             // Store the timestamp of the press
    }

    // Button released: Quick press or single hold action
    if (buttons[i].rose()) {
      unsigned long pressDuration = millis() - pressStartTime[i];
      if (pressDuration < holdThreshold) { // Quick press (less than 500ms)
        switch (i) {
          case 0:
            Serial.println("Quick press: + - Profile 1");
            bleKeyboard.write('+');
            break;
          case 1:
            Serial.println("Quick press: - - Profile 1");
            bleKeyboard.write('-');
            break;
          case 2:
            Serial.println("Quick press: r - Profile 1");
            bleKeyboard.write('r');
            break;
          case 3:
            Serial.println("Quick press: c - Profile 1");
            bleKeyboard.write('c');
            break;
        }
      } else { // Single hold action (more than 500ms)
        switch (i) {
          case 0:
            // Button 0: No single hold action (repeated actions handled below)
            break;
          case 1:
            // Button 1: No single hold action (repeated actions handled below)
            break;
          case 2:
            Serial.println("Hold: m - Profile 1");
            bleKeyboard.write('m'); 
            break;
          case 3:
            Serial.println("Hold: d - Profile 1");
            bleKeyboard.write('d');
            break;
        }
      }
    }

    // Repeating hold actions (only for Button 0 and Button 1)
    if ((buttons[i].read() == LOW) && (i == 0 || i == 1)) { // Button is held down for buttons 0 and 1
      unsigned long pressDuration = millis() - pressStartTime[i];
      unsigned long currentTime = millis();

      if (pressDuration >= holdThreshold) { // If holding for 500ms or more
        if (currentTime - lastHoldActionTime[i] >= repeatInterval) { // Perform hold action at repeat interval
          switch (i) {
            case 0:
              Serial.println("Repeat Hold: = - Profile 1");
              bleKeyboard.write('=');
              break;
            case 1:
              Serial.println("Repeat Hold: -- - Profile 1");
              bleKeyboard.write('_');
              break;
          }
          lastHoldActionTime[i] = currentTime; // Update the last hold action time
        }
      }
    }
  }
}



// Function to handle Profile 2
void handleProfile2() {
  delay(100);
}
