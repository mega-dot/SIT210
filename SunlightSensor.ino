#include <WiFiNINA.h>
#include "secrets.h" 

WiFiClient client;

char HOST_NAME[] = "maker.ifttt.com";
String sunlightWebhook = "/trigger/Sunlight_detected/with/key/l0d3ZPywewAYjwTdLHZi1h8JEfqaor-B0c7_t0BVrZ9";
String noSunlightWebhook = "/trigger/no_sunlight/with/key/l0d3ZPywewAYjwTdLHZi1h8JEfqaor-B0c7_t0BVrZ9";

String queryString = "?value1=";


int lightSensorPin = A0;  
int lightThreshold = 500; 

void setup() {
  Serial.begin(9600);
  while (!Serial);

  
  WiFi.begin(SECRET_SSID, SECRET_PASSWORD);
  Serial.print("Connecting to WiFi");

  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  
  if (client.connect(HOST_NAME, 80)) {
    Serial.println("Connected to IFTTT");
  } else {
    Serial.println("Connection to IFTTT failed");
  }
}

void loop() {
  int sensorValue = analogRead(lightSensorPin); // Read from light sensor

  
  Serial.print("Sensor value: ");
  Serial.println(sensorValue);

  
  if (sensorValue > lightThreshold) {
    queryString = "?value1=SunlightDetected";  // Send Sunlight Detected
    Serial.println("Sunlight detected");

    // Send HTTP request to Sunlight webhook
    sendWebhookRequest(sunlightWebhook);
  } else {
    queryString = "?value1=NoSunlightDetected";  // Send No Sunlight Detected
    Serial.println("No sunlight detected");

    // Send HTTP request to No Sunlight webhook
    sendWebhookRequest(noSunlightWebhook);
  }

  delay(60000); // Wait for 60 seconds before checking again
}


void sendWebhookRequest(String webhook) {
  // Send HTTP request to IFTTT
  if (client.connect(HOST_NAME, 80)) {
    client.println("GET " + webhook + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // End HTTP header
  } else {
    Serial.println("Failed to connect to server");
  }

  
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
  }

  // Disconnect client
  client.stop();
  Serial.println("\nDisconnected");
}
