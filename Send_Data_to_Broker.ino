#include <DHTesp.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

/* Created by: Muhammad Jihadil (jihadil003@gmail.com)
 * Publication: https://drive.google.com/file/d/1366n3-IRN7HiNp7mXm9MVnSAszm46DyY/view?usp=share_link
 * 
 * Make sure you have installed the ESP8266 board:
 * Go to Preferences
 * Add "http://arduino.esp8266.com/stable/package_esp8266com_index.json" in "Additional Boards Manager URLs"
 * Go to Boards Manager
 * Install ESP8266 board
 */

DHTesp dht;         // Define DHT11
WiFiClient client;  // Declare object of class WiFiClient
HTTPClient http;    // Declare object of class HTTPClient

// Network SSID
const char* ssid = "JIHADIL Laptop";
const char* password = "123456";

// Broker location in your server
const char* broker = "http://192.168.137.1:81/broker.php";

// Machine ID and location
String idMesin = "131002";
String lokasi = "B";

int relay = 0;  // Relay, 0 in arduino IDE equal to D3 in Wemos D1 Mini board

// Temperature limit
int Tmax = 40;  // Maximum temperature
int Tmin = 37;  // Minimum temperature

void setup() {

  //Setup
  Serial.begin(9600);
  pinMode(relay, OUTPUT);       // Relay setup    
  dht.setup(12,DHTesp::DHT11);  // Setup sensor DHT11, 12 in arduino IDE equal to D3 in Wemos D6 Mini board
  
  // Connect to WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.hostname("Wemos_Jihadil");
  WiFi.begin(ssid, password);

  // Wating to connect to WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Connected to WiFi
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Print the IP address
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());

}
 
void loop() {

  int temperature = dht.getTemperature(); // Get temperature data
  digitalWrite(relay, LOW);               // In initial condition, relay is off

  if(temperature < Tmin){
    digitalWrite(relay, HIGH);  // Relay will on when temperature < temperature minimum
    
    while(temperature <= Tmax){               // Rasing the temperature
      delay(2000);                            // Refresh data every 2 seconds
      int temperature = dht.getTemperature(); // Get temperature data
      int response = sendData(temperature);   // Sending data
    }
    
  }
  else{
    while(temperature >= Tmin){               // Lowering the temperature while relay off
      delay(2000);                            // Refresh data every 2 seconds
      int temperature = dht.getTemperature(); // Get temperature data
      int response = sendData(temperature);   // Sending data
    }
  }
  
}

// Sending data function
int sendData(int temperature){
  int response; // Declare response variable
  
  if(WiFi.status()== WL_CONNECTED){                                       // Check WiFi connection status
    http.begin(client, broker);                                           // Specify request destination
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");  // Specify content-type header
    
    // Generate requested data
    String httpRequestData = "Temperatur=" + String(temperature) + "&idMesin=" + idMesin + "&location=" + lokasi;  
 
    int httpCode = http.POST(httpRequestData);  // Send the requested data
    String payload = http.getString();          // Get the response payload
 
    Serial.println(httpCode); // Print HTTP return code
    Serial.println(payload);  // Print request response payload
    response = 1;             // Data have been sent
    http.end();               // Close connection
    }
  else{
    Serial.println("Error in WiFi connection"); // WiFi connection error
    response = 0;                               // Data haven't been sent
    }
    
  return response;
}
