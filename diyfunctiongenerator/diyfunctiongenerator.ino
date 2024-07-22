#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display width and height
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Number of samples to capture
#define NUM_SAMPLES 128
#define SAMPLE_RATE 10000  // Adjust the sampling rate if needed

// Array to hold samples
int samples[NUM_SAMPLES];

// Variables for ADC timing
unsigned long lastSampleTime = 0;
unsigned int sampleInterval = 1000000 / SAMPLE_RATE;  // Interval in microseconds

// Vertical offset control buttons
#define INCREASE_PIN 2
#define DECREASE_PIN 3

// Vertical offset variable
int verticalOffset = 0;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Clear the buffer
  display.clearDisplay();
  display.display();

  // Set A0 as input with internal pull-up resistor
  pinMode(A0, INPUT);

  // Set buttons as input with pull-up resistors
  pinMode(INCREASE_PIN, INPUT_PULLUP);
  pinMode(DECREASE_PIN, INPUT_PULLUP);
}

void loop() {
  // Check button states
  if (digitalRead(INCREASE_PIN) == LOW) {
    verticalOffset += 1;
    delay(100);  // Debounce delay
  }
  if (digitalRead(DECREASE_PIN) == LOW) {
    verticalOffset -= 1;
    delay(100);  // Debounce delay
  }

  // Ensure verticalOffset is within a reasonable range
  verticalOffset = constrain(verticalOffset, -30, 30);

  // Capture samples at the defined sampling rate
  for (int i = 0; i < NUM_SAMPLES; i++) {
    while (micros() - lastSampleTime < sampleInterval) {
      // Wait for the next sample time
    }
    samples[i] = analogRead(A0);  // Read from A0
    lastSampleTime = micros();
  }

  // Clear the display
  display.clearDisplay();

  // Plot the waveform on the OLED
  for (int i = 1; i < NUM_SAMPLES; i++) {
    int x0 = map(i - 1, 0, NUM_SAMPLES - 1, 0, SCREEN_WIDTH - 1);
    int y0 = map(samples[i - 1], 0, 1023, SCREEN_HEIGHT - 1, 0) + verticalOffset;
    int x1 = map(i, 0, NUM_SAMPLES - 1, 0, SCREEN_WIDTH - 1);
    int y1 = map(samples[i], 0, 1023, SCREEN_HEIGHT - 1, 0) + verticalOffset;

    // Ensure y values are within screen bounds
    y0 = constrain(y0, 0, SCREEN_HEIGHT - 1);
    y1 = constrain(y1, 0, SCREEN_HEIGHT - 1);

    display.drawLine(x0, y0, x1, y1, SSD1306_WHITE);
  }

  // Display the buffer
  display.display();

  // Small delay to avoid overloading the display
  delay(50);
}
