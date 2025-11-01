#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_camera.h"

// Wi-Fi credentials
const char* ssid = "***********";
const char* password = "***********";

// First server details
const char* firstServerHost = "***********";
const String firstServerPath = "***********";
const int firstServerPort = ***********;

// Second server details (Update this with your computer's IP)
const char* secondServerHost = "***********"; // Replace with your computer's IP
const int secondServerPort = ***********;

// Camera model configuration
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

void connectToWiFi();
void sendPhoto();
void sendToSecondServer(String text);

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200);

  connectToWiFi();

  // Camera setup
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 5;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x\n", err);
    delay(1000);
    ESP.restart();
  }
}

void loop() {
  Serial.println("Capturing image...");
  sendPhoto();
  delay(50000);
}

void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");
}

void sendPhoto() {
  camera_fb_t* fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    delay(1000);
    ESP.restart();
  }

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();

    if (client.connect(firstServerHost, firstServerPort)) {
      Serial.println("Connected to first server!");

      // Prepare HTTP POST request
      String bodyStart = "--Boundary123\r\n"
                         "Content-Disposition: form-data; name=\"imageFile\"; filename=\"esp32-cam.jpg\"\r\n"
                         "Content-Type: image/jpeg\r\n\r\n";
      String bodyEnd = "\r\n--Boundary123--\r\n";
      int bodyLength = bodyStart.length() + fb->len + bodyEnd.length();

      client.println("POST " + firstServerPath + " HTTP/1.1");
      client.println("Host: " + String(firstServerHost));
      client.println("Content-Type: multipart/form-data; boundary=Boundary123");
      client.println("Content-Length: " + String(bodyLength));
      client.println("Connection: close");
      client.println();
      client.print(bodyStart);
      client.write(fb->buf, fb->len);
      client.print(bodyEnd);

      // Read response
      String response = "";
      while (client.connected() || client.available()) {
        if (client.available()) {
          response += (char)client.read();
        }
      }
      client.stop();
      Serial.println("Response from first server:");
      Serial.println(response);

      // Extract text from the response
      int startIndex = response.indexOf("\r\n\r\n") + 4; // Start after headers
      String extractedText = response.substring(startIndex);
      extractedText.trim(); // Remove any surrounding whitespace or newline characters

      // Remove quotes and newline characters from the extracted text
      if (extractedText.startsWith("\"") && extractedText.endsWith("\"")) {
        extractedText = extractedText.substring(1, extractedText.length() - 1);
      }
      extractedText.replace("\\n", ""); // Remove escaped newlines (\n)
      Serial.println("Extracted text: " + extractedText);

      // Send extracted text to the second server
      sendToSecondServer(extractedText);

    } else {
      Serial.println("Connection to first server failed!");
    }
  } else {
    Serial.println("Wi-Fi not connected.");
  }

  esp_camera_fb_return(fb);
}


void sendToSecondServer(String text) {
  WiFiClient client;

  if (client.connect(secondServerHost, secondServerPort)) {
    Serial.println("Connected to second server!");

    // Escape text for JSON compatibility
    String escapedText = escapeJSONString(text);

    // Prepare JSON payload
    String payload = "{\"text\": \"" + escapedText + "\", \"model\": \"aura-asteria-en\"}";

    // Log payload for debugging
    Serial.println("Sending payload:");
    Serial.println(payload);

    // Send HTTP POST request
    client.println("POST /api HTTP/1.1");
    client.println("Host: " + String(secondServerHost));
    client.println("Content-Type: application/json");
    client.println("Content-Length: " + String(payload.length()));
    client.println("Connection: close");
    client.println();
    client.print(payload);

    // Read response
    String response = "";
    while (client.connected() || client.available()) {
      if (client.available()) {
        char c = client.read();
        response += c;
        Serial.print(c); // Print each character of the response
      }
    }


    client.stop();
    Serial.println("\nResponse from second server:");
    Serial.println(response);


    // Handle the response (e.g., save the audio URL)
  } else {
    Serial.println("Failed to connect to the second server. Check IP, port, and server status.");
  }
}

String escapeJSONString(String str) {
  String escaped = "";
  for (int i = 0; i < str.length(); i++) {
    char c = str[i];
    if (c == '\"') escaped += "\\\"";
    else if (c == '\\') escaped += "\\\\";
    else if (c == '/') escaped += "\\/";
    else if (c == '\b') escaped += "\\b";
    else if (c == '\f') escaped += "\\f";
    else if (c == '\n') escaped += "\\n";
    else if (c == '\r') escaped += "\\r";
    else if (c == '\t') escaped += "\\t";
    else escaped += c;
  }
  return escaped;
}

