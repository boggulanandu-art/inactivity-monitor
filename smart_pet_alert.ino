/*
 * ============================================================
 *  Smart Pet Activity Alert System
 *  Platform : Arduino Uno / ESP32 (select correct board)
 *  Sensor   : PIR Motion Sensor (HC-SR501)//logicstate
 *  Alert    : LED + Buzzer{speaker}

 * ============================================================
 *
 *  LOGIC:
 *   1. Pet ACTIVE  → PIR detects motion → Green LED ON, no buzzer.
 *   2. Pet INACTIVE → No motion for INACTIVITY_THRESHOLD ms
 *                  → Red LED blinks + Buzzer beeps (alert).
 *   3. All events printed to Serial Monitor (9600 baud).
 * ============================================================
 */

// -------- PIN DEFINITIONS --------
const int PIR_PIN       = 2;   // PIR signal pin  → D2
const int GREEN_LED_PIN = 8;   // Activity LED    → D8
const int RED_LED_PIN   = 9;   // Alert LED       → D9
const int BUZZER_PIN    = 10;  // Passive buzzer  → D10

// -------- CONFIGURATION --------
// How long (ms) without motion before alert triggers
const unsigned long INACTIVITY_THRESHOLD = 10000UL;  // 10 seconds

// Buzzer tone frequency (Hz) – passive buzzer only
const int BUZZER_FREQ = 1000;

// Serial baud rate
const int BAUD_RATE = 9600;

// -------- STATE VARIABLES --------
bool     motionDetected     = false;
bool     alertActive        = false;
bool     lastMotionState    = false;
unsigned long lastMotionTime = 0;
unsigned long alertStartTime = 0;

// For non-blocking LED blink
unsigned long lastBlinkTime  = 0;
bool          blinkState     = false;
const unsigned long BLINK_INTERVAL = 400; // ms

// -------- SETUP --------
void setup() {
  Serial.begin(BAUD_RATE);

  pinMode(PIR_PIN,       INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN,   OUTPUT);
  pinMode(BUZZER_PIN,    OUTPUT);

  // Startup sequence – visual confirmation
  Serial.println("===========================================");
  Serial.println("  Smart Pet Activity Alert System");
  Serial.println("  Warming up PIR sensor (5 seconds)...");
  Serial.println("===========================================");

  // PIR warm-up: keep LEDs in standby pattern
  for (int i = 0; i < 5; i++) {
    digitalWrite(GREEN_LED_PIN, HIGH);
    delay(300);
    digitalWrite(GREEN_LED_PIN, LOW);
    delay(700);
  }

  lastMotionTime = millis();  // avoid instant false alert
  Serial.println("[SYSTEM] Ready – monitoring pet activity.\n");
}

// -------- MAIN LOOP --------
void loop() {
  unsigned long now = millis();

  // 1. Read PIR sensor
  motionDetected = (digitalRead(PIR_PIN) == HIGH);

  // 2. Handle motion detection
  if (motionDetected) {
    lastMotionTime = now;

    if (!lastMotionState) {
      // Rising edge – pet just became active
      Serial.print("[MOTION] Activity detected at ");
      printTimestamp(now);
    }

    // Pet is active: green LED on, cancel any alert
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN,   LOW);
    noTone(BUZZER_PIN);
    alertActive = false;

  } else {
    // No current motion
    digitalWrite(GREEN_LED_PIN, LOW);

    if (lastMotionState && !alertActive) {
      // Falling edge – pet just stopped moving
      Serial.print("[INFO]   Motion ended at ");
      printTimestamp(now);
    }

    // Check inactivity duration
    unsigned long elapsed = now - lastMotionTime;

    if (elapsed >= INACTIVITY_THRESHOLD) {
      // ---- ALERT CONDITION ----
      if (!alertActive) {
        alertActive   = true;
        alertStartTime = now;
        Serial.println("[ALERT]  *** No pet movement detected! ***");
        Serial.print("         Inactivity duration: ");
        Serial.print(elapsed / 1000);
        Serial.println(" seconds");
        Serial.println("         Check on your pet!");
      }

      // Non-blocking red LED blink
      if (now - lastBlinkTime >= BLINK_INTERVAL) {
        lastBlinkTime = now;
        blinkState    = !blinkState;
        digitalWrite(RED_LED_PIN, blinkState ? HIGH : LOW);

        // Beep buzzer in sync with LED
        if (blinkState) {
          tone(BUZZER_PIN, BUZZER_FREQ, BLINK_INTERVAL / 2);
        }
      }

      // Repeat serial alert every 5 seconds
      if ((now - alertStartTime) % 5000 < 20) {
        Serial.print("[ALERT]  Still no movement – total inactivity: ");
        Serial.print(elapsed / 1000);
        Serial.println(" s");
      }

    } else {
      // Within threshold – just waiting
      digitalWrite(RED_LED_PIN, LOW);
      noTone(BUZZER_PIN);

      // Optional: print countdown every 3 seconds
      if (!alertActive && (elapsed > 0) && (elapsed % 3000 < 20)) {
        Serial.print("[INFO]   Waiting... ");
        Serial.print((INACTIVITY_THRESHOLD - elapsed) / 1000);
        Serial.println(" s until inactivity alert.");
      }
    }
  }

  lastMotionState = motionDetected;
  delay(50);  // Small debounce delay (50 ms loop tick)
}

// -------- HELPER: PRINT TIMESTAMP --------
void printTimestamp(unsigned long ms) {
  unsigned long totalSec = ms / 1000;
  unsigned int  h = totalSec / 3600;
  unsigned int  m = (totalSec % 3600) / 60;
  unsigned int  s = totalSec % 60;
  char buf[16];
  snprintf(buf, sizeof(buf), "%02u:%02u:%02u\n", h, m, s);
  Serial.print(buf);
}
