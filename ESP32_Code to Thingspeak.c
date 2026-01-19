#include <SPI.h>
#include <mcp2515.h>
#include <WiFi.h>
#include <HTTPClient.h>

// ---------- MCP2515 Setup ----------
struct can_frame canMsg;
MCP2515 mcp2515(5);  // CS pin — use GPIO5 (change if wired differently)

// ---------- Wi-Fi Credentials ----------
const char* ssid = "Flybox-7091";
const char* password = "12345678";

// ---------- ThingSpeak Info ----------
const char* server = "*********************";
const char* apiKey = "*********************";

void setup() {
  Serial.begin(115200);
  SPI.begin();  // Initialize SPI for MCP2515

  // Initialize MCP2515
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  Serial.println("========================================");
  Serial.println("   BMS CAN DECODER - ESP32 WROOM");
  Serial.println("   Reading SoC & Current + ThingSpeak");
  Serial.println("========================================");
  Serial.println("Connecting to Wi-Fi...");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n Connected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read CAN message
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    if (canMsg.can_id == 0x98FF28F4) {  // Check CAN ID
      byte soc = canMsg.data[1];
      uint16_t currentRaw = (canMsg.data[3] << 8) | canMsg.data[2];
      float current = (5000 - currentRaw) * 0.1;

      // ---------- Display in Serial Monitor ----------
      Serial.println("========================================");
      Serial.println("        BMS DATA RECEIVED");
      Serial.println("========================================");
      Serial.print("State of Charge (SoC): ");
      Serial.print(soc);
      Serial.println(" %");

      Serial.print("Current: ");
      Serial.print(current, 1);
      Serial.print(" A ");
      Serial.println(current >= 0 ? "[CHARGING/IDLE]" : "[DISCHARGING]");
      Serial.println();

      // ---------- Send to ThingSpeak ----------
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(soc) + "&field2=" + String(current);
        http.begin(url);
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0) {
          Serial.print("Data sent to ThingSpeak (Response: ");
          Serial.print(httpResponseCode);
          Serial.println(")");
        } else {
          Serial.print("ThingSpeak send failed, error: ");
          Serial.println(httpResponseCode);
        }

        http.end();
      } else {
        Serial.println("Wi-Fi disconnected, reconnecting...");
        WiFi.reconnect();
      }

      delay(20000);  // ThingSpeak allows 15 seconds minimum between updates
    }
  }
}