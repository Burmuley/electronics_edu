#ifdef DEBUG_ESP_PORT
#define DEBUG_MSG(...) DEBUG_ESP_PORT.printf( __VA_ARGS__ )
#else
#define DEBUG_MSG(...)
#endif

static const uint8 S_DTA = D1; // DATA pin D1
static const uint8 S_LTC = D2; // LATCH pin D2
static const uint8 S_CLK = D5; // CLOCK pin D5

// numbers
static const uint8 nums[10] = {
  126, // 0
  48,  // 1
  109, // 2
  121, // 3
  51,  // 4
  91,  // 5
  95,  // 6
  112, // 7
  127, // 8
  123, // 9
};

// letters
static const uint8 lets[10] = {
  119, // A
  78,  // C
  79,  // E
  71,  // F
  55,  // H
  56,  // J
  14,  // L
  126, // O
  103, // P
  91,  // S
};

void setup() {
  Serial.begin(74880);
  pinMode(S_DTA, OUTPUT);
  pinMode(S_LTC, OUTPUT);
  pinMode(S_CLK, OUTPUT);

}

void loop() {
  updateShiftRegister(0);
  delay(10);

// display numbers
  for (int i = 0; i < sizeof(nums); i++) {
    DEBUG_MSG("NUMBER: %d\n", i);
    updateShiftRegister(nums[i]);
    delay(500);

  }

// display letters
  for (int i = 0; i < sizeof(lets); i++) {
    DEBUG_MSG("LETTER: %d\n", i);
    updateShiftRegister(lets[i]);
    delay(500);
  }
}

void updateShiftRegister(byte data) {
  DEBUG_MSG("DATA: %d\n", data);
  digitalWrite(S_LTC, LOW);               // set LATCH to LOW
  shiftOut(S_DTA, S_CLK, LSBFIRST, data); // send data to shift register
  digitalWrite(S_LTC, HIGH);              // set LATCH to HIGH to reflect new settings on outputs
}
