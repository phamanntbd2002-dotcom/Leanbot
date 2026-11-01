#include <Leanbot.h>  // Leanbot library
 
const int micPin = A6;  // Microphone sensor pin
const int threshold = 700;  // Set noise detection threshold
 
void setup() {
    Leanbot.begin();       // Initialize Leanbot
    Serial.begin(9600);    // Start Serial Monitor
}
 
void loop() {
    int soundLevel = analogRead(micPin);  // Read microphone sensor value
 
    Serial.print("Sound Level: ");
    Serial.println(soundLevel);  // Display sound level in Serial Monitor
 
    if (soundLevel > threshold) {  // Check if sound exceeds the threshold
        Serial.println("Loud Sound Detected!");
        LbRGB.fillColor(0xff0000, BITMAP(ledO, ledA, ledB, ledC, ledD, ledE, ledF)); // Red LED alert
        LbRGB.show();
        Leanbot.tone(500, 200);  // Optional: Sound a buzzer alert
    } else {
        LbRGB.fillColor(0x00ff00, BITMAP(ledO, ledA, ledB, ledC, ledD, ledE, ledF)); // Green LED (Normal)
        LbRGB.show();
    }
 
    delay(200);  // Delay to stabilize readings
}