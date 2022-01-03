#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid     = "your_wifi_name";
const char* password = "your_wifi_password";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://your-domain.com/TX.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9";

int LED_BUILTIN = 2;
bool led_status;
String sensorName = "Led";
String sensorLocation = "Board";

int pushbutton = 15; // declara o push button na porta 15

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode (LED_BUILTIN, OUTPUT); // define LED como saida
  pinMode(pushbutton, INPUT_PULLUP); // define o pino do botao como entrada
  led_status = 0; //initial led state
}

void loop() {
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
      String payload = httpGETRequest(serverName);
      Serial.println(payload);

      // Stream& input;
      StaticJsonDocument<768> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }

      const char* id = doc["id"]; // "99999"
      const char* PASSWORD = doc["PASSWORD"]; // "12345"
      const char* SENT_NUMBER_1 = doc["SENT_NUMBER_1"]; // "327"
      const char* SENT_NUMBER_2 = doc["SENT_NUMBER_2"]; // "1212"
      const char* SENT_NUMBER_3 = doc["SENT_NUMBER_3"]; // "3233"
      const char* SENT_NUMBER_4 = doc["SENT_NUMBER_4"]; // "1313"
      const char* SENT_BOOL_1 = doc["SENT_BOOL_1"]; // "1"
      const char* SENT_BOOL_2 = doc["SENT_BOOL_2"]; // "1"
      const char* SENT_BOOL_3 = doc["SENT_BOOL_3"]; // "1"
      const char* RECEIVED_BOOL1 = doc["RECEIVED_BOOL1"]; // "0"
      const char* RECEIVED_BOOL2 = doc["RECEIVED_BOOL2"]; // "1"
      const char* RECEIVED_BOOL3 = doc["RECEIVED_BOOL3"]; // "1"
      const char* RECEIVED_BOOL4 = doc["RECEIVED_BOOL4"]; // "0"
      const char* RECEIVED_NUM1 = doc["RECEIVED_NUM1"]; // "0"
      const char* RECEIVED_NUM2 = doc["RECEIVED_NUM2"]; // "0"
      const char* RECEIVED_NUM3 = doc["RECEIVED_NUM3"]; // "0"
      const char* RECEIVED_NUM4 = doc["RECEIVED_NUM4"]; // "0"

      
      led_status = *RECEIVED_BOOL1=='1'; // converting char to bool
      Serial.println(led_status);
  
      if (digitalRead(pushbutton) == LOW){ // Se o botão for pressionado
        // Prepare your HTTP POST request data
        led_status = !led_status; // troca o estado do LED
        while (digitalRead(pushbutton) == LOW);
        httpPOSTRequest(serverName, apiKeyValue, "RECEIVED_BOOL1", String(led_status));
        
      }
      else{
        
      }
  }
  else {
    Serial.println("WiFi Disconnected");
  }

  digitalWrite(LED_BUILTIN, led_status);
  delay(10);  
}


String httpGETRequest(const char* serverName) {
  HTTPClient http;

  // Your IP address with path or Domain name with URL path 
  http.begin(serverName);

  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload = "{}"; 

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

void httpPOSTRequest(const char* serverName, String apiKey, String column, String value) {
  HTTPClient http;

  // Your IP address with path or Domain name with URL path 
  http.begin(serverName);
  
  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Prepare your HTTP POST request data
  String httpRequestData = "api_key=" + apiKey + "&column=" + column
                            + "&value=" + value + "";
  Serial.print("httpRequestData: ");
  Serial.println(httpRequestData);
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(httpRequestData);

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

}
