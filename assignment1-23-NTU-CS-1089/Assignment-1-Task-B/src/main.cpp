//Assignment-1 Task B
//Iot And Embedded Systems
//BSCS 5TH B
//Name : Sajal Naeem    Roll No:23-NTU-CS-1089



#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//  Pin Definitions 
#define BUTTON_PIN 25     
#define LED_PIN 18         
#define BUZZER_PIN 27     
#define SDA_PIN 21         
#define SCL_PIN 22         

//  OLED Setup 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Globals 
bool ledState = false;
bool buttonPressed = false;
unsigned long pressStartTime = 0;
const unsigned long longPressDuration = 1500; 

//  Display message 
void showMessage(const String &msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.print(msg);
  display.display();
}

// Setup 
void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize OLED
  Wire.begin(SDA_PIN, SCL_PIN);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (true);
  }
  display.clearDisplay();
  display.display();

  showMessage("System Ready");
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

//  Loop
void loop() {
  bool btnState = digitalRead(BUTTON_PIN);
// btn state =low;

  if (!btnState && !buttonPressed) { // btn state = high 
    buttonPressed = true;             // btn state actual=low
    pressStartTime = millis();
  }

  // Button held down
  if (buttonPressed && !btnState) {// btn state =high // actual=low
    unsigned long pressDuration = millis() - pressStartTime;
    if (pressDuration > longPressDuration) {
      
      showMessage("Long Press");
      
      tone(BUZZER_PIN, 2000); 

      
    }
  }

  // Button released
  if (buttonPressed && btnState) { 
    unsigned long pressDuration = millis() - pressStartTime;
    buttonPressed = false;

    // Stop buzzer
    noTone(BUZZER_PIN);
    digitalWrite(BUZZER_PIN, LOW);

    if (pressDuration <= longPressDuration) {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
      showMessage("Short Press");
    }
  }
}
