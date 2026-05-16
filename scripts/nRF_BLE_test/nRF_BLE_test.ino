
#include <bluefruit.h>

// XIAO nRF52840 RGB LED pins (active LOW)
#define LED_RED   11
#define LED_GREEN 12
#define LED_BLUE  13

BLEDis  bledis;
BLEUart bleuart;

void setup() {
  Serial.begin(115200);

  // RGB LED pins setup (active LOW on XIAO)
  pinMode(LED_RED,   OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE,  OUTPUT);

  // Turn all off initially (HIGH = off for active low)
  digitalWrite(LED_RED,   HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE,  HIGH);

  // --- BLE Setup ---
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("XIAO-nRF52840-Test");

  bledis.setManufacturer("Seeed Studio");
  bledis.setModel("XIAO nRF52840");
  bledis.begin();

  bleuart.begin();

  startAdv();

  Serial.println("==============================");
  Serial.println(" XIAO nRF52840 Test Firmware");
  Serial.println("==============================");
  Serial.println("[OK] Board booted successfully");
  Serial.println("[OK] BLE advertising started");
  Serial.println("     Device name: XIAO-nRF52840-Test");
  Serial.println("     Scan with nRF Connect app to verify BLE");
  Serial.println("------------------------------");
  Serial.println("[OK] RGB LED test starting...");
}

void startAdv() {
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); // in units of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0); // 0 = advertise forever
}

void setRGB(bool r, bool g, bool b) {
  // Active LOW: true = ON means write LOW
  digitalWrite(LED_RED,   r ? LOW : HIGH);
  digitalWrite(LED_GREEN, g ? LOW : HIGH);
  digitalWrite(LED_BLUE,  b ? LOW : HIGH);
}

void loop() {
  // --- RGB LED Cycle Test ---
  Serial.println("[TEST] RED");
  setRGB(true, false, false);
  delay(500);

  Serial.println("[TEST] GREEN");
  setRGB(false, true, false);
  delay(500);

  Serial.println("[TEST] BLUE");
  setRGB(false, false, true);
  delay(500);

  Serial.println("[TEST] WHITE (all on)");
  setRGB(true, true, true);
  delay(500);

  Serial.println("[TEST] OFF");
  setRGB(false, false, false);
  delay(500);

  // --- BLE Status ---
  if (Bluefruit.connected()) {
    Serial.println("[BLE] Client connected!");
    setRGB(false, true, false); // solid green = connected

    // Echo any received BLE UART data back
    while (bleuart.available()) {
      String msg = bleuart.readString();
      Serial.print("[BLE] Received: ");
      Serial.println(msg);
      bleuart.print("Echo: ");
      bleuart.println(msg);
    }
    delay(1000);
  } else {
    Serial.println("[BLE] Advertising... (not connected)");
  }

  Serial.println("------------------------------");
}
