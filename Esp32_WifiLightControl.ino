#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"
#include <WiFi.h>

// Wi-Fi network details
const char* ssid = "NETWORK-SSID";
const char* password = "NETWORK-PASSWORD";

// Server details
const char* serverIP = "IP OF YOUR DEVICE";
const int serverPort = 5577;

// Rotary encoder pin configuration
#define ROTARY_ENCODER_A_PIN 23
#define ROTARY_ENCODER_B_PIN 22
#define ROTARY_ENCODER_BUTTON_PIN 21
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4

WiFiClient client;
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

int color = 0;
int brightness = 0;
uint8_t packet[13];

// Function to set color and brightness
void setColorBrightness(uint8_t *command) {
  command[0] = 0x3b;
  command[1] = 0xa1;
  command[2] = 0x00;
  command[3] = 0x64;
  command[4] = brightness;

  for(int i=5; i<12; i++) {
    command[i] = 0x00;
  }

  // Set color based on 'color' value
  switch (color) {
    case 0: // White
      command[2] = 0x00;
      command[3] = 0x00;
      break;
    case 1: // Red
      command[2] = 0x00;
      break;
    case 2: // Green
      command[2] = 0x3c;
      break;
    case 3: // Blue
      command[2] = 0x78;
      break;
  }

  // Compute checksum
  command[12] = 0; 
  for (int i = 0; i < 12; i++) {
    command[12] += command[i];
  }
  command[12] = ~command[12] + 1; 
}

// Function to print packet
void printPacket(uint8_t *packet, int size) {
  for(int i=0; i<size; i++) {
    if(packet[i] < 0x10) {
      Serial.print("0"); 
    }
    Serial.print(packet[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

// Function for handling button click
void rotary_onButtonClick()
{
    static unsigned long lastTimePressed = 0; 
    if (millis() - lastTimePressed < 500)
    {
            return;
    }
    lastTimePressed = millis();
    
    color = (color >= 3) ? 0 : ++color;

    changeLight();
}

// Function to handle rotary loop
void rotary_loop()
{
    if (rotaryEncoder.encoderChanged())
    {
            brightness = rotaryEncoder.readEncoder();
            changeLight();
            Serial.print("Value: ");
            Serial.println(brightness);
    }
    if (rotaryEncoder.isEncoderButtonClicked())
    {
            rotary_onButtonClick();
    }
}

// ISR for handling rotary encoder reading
void IRAM_ATTR readEncoderISR()
{
    rotaryEncoder.readEncoder_ISR();
}

// Function to change light
void changeLight(){
if (client.connect(serverIP, serverPort)) {
      Serial.println("TCP Connection established!");

      setColorBrightness(packet);

      client.write(packet, sizeof(packet));

      Serial.print("Packet sent: ");
      printPacket(packet, sizeof(packet));

      client.stop();
      Serial.println("TCP Connection closed.");
    } else {
      Serial.println("Unable to establish TCP Connection.");
    }
}

void setup()
{
    Serial.begin(115200);
    rotaryEncoder.begin();
    rotaryEncoder.setup(readEncoderISR);
    
    bool circleValues = false;
    rotaryEncoder.setBoundaries(0, 100, circleValues); 

    rotaryEncoder.setAcceleration(250); 

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
    }

    Serial.println("WiFi Connection established!");

    changeLight();
}

void loop()
{
    rotary_loop();
    delay(50);
}
