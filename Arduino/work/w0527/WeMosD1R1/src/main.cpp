/**

  GPIO 0 – Button right / D3
  GPIO 1 – D10
  GPIO 2 – LED blue (LED_BUILTIN) / D4
  GPIO 3 – D9
  GPIO 4 – OLED SCL
  GPIO 5 – OLED SDA
  GPIO 12 – Button down
  GPIO 13 – Button up
  GPIO 14 – Button push
  GPIO 15 – D8
  GPIO 16 – LED green
  GPIO A0 – ADC

**/

#include "SSD1306Brzo.h" // Include OLED Library

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#ifndef STASSID
#define STASSID "zigishi"
#define STAPSK  "UnitePlug!3"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "api.github.com";
const int httpsPort = 443;

// DigiCert High Assurance EV Root CA
const char trustRoot[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDxTCCAq2gAwIBAgIQAqxcJmoLQJuPC3nyrkYldzANBgkqhkiG9w0BAQUFADBs
MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3
d3cuZGlnaWNlcnQuY29tMSswKQYDVQQDEyJEaWdpQ2VydCBIaWdoIEFzc3VyYW5j
ZSBFViBSb290IENBMB4XDTA2MTExMDAwMDAwMFoXDTMxMTExMDAwMDAwMFowbDEL
MAkGA1UEBhMCVVMxFTATBgNVBAoTDERpZ2lDZXJ0IEluYzEZMBcGA1UECxMQd3d3
LmRpZ2ljZXJ0LmNvbTErMCkGA1UEAxMiRGlnaUNlcnQgSGlnaCBBc3N1cmFuY2Ug
RVYgUm9vdCBDQTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMbM5XPm
+9S75S0tMqbf5YE/yc0lSbZxKsPVlDRnogocsF9ppkCxxLeyj9CYpKlBWTrT3JTW
PNt0OKRKzE0lgvdKpVMSOO7zSW1xkX5jtqumX8OkhPhPYlG++MXs2ziS4wblCJEM
xChBVfvLWokVfnHoNb9Ncgk9vjo4UFt3MRuNs8ckRZqnrG0AFFoEt7oT61EKmEFB
Ik5lYYeBQVCmeVyJ3hlKV9Uu5l0cUyx+mM0aBhakaHPQNAQTXKFx01p8VdteZOE3
hzBWBOURtCmAEvF5OYiiAhF8J2a3iLd48soKqDirCmTCv2ZdlYTBoSUeh10aUAsg
EsxBu24LUTi4S8sCAwEAAaNjMGEwDgYDVR0PAQH/BAQDAgGGMA8GA1UdEwEB/wQF
MAMBAf8wHQYDVR0OBBYEFLE+w2kD+L9HAdSYJhoIAu9jZCvDMB8GA1UdIwQYMBaA
FLE+w2kD+L9HAdSYJhoIAu9jZCvDMA0GCSqGSIb3DQEBBQUAA4IBAQAcGgaX3Nec
nzyIZgYIVyHbIUf4KmeqvxgydkAQV8GK83rZEWWONfqe/EW1ntlMMUu4kehDLI6z
eM7b41N5cdblIZQB2lWHmiRk9opmzN6cN82oNLFpmyPInngiK3BD41VHMWEZ71jF
hS9OMPagMRYjyOfiZRYzy78aG6A9+MpeizGLYAiJLQwGXFK3xPkKmNEVX58Svnw2
Yzi9RKR/5CYrCsSXaQ3pjOLAEFe4yHYSkVXySGnYvCoCWw9E1CAx2/S6cCZdkGCe
vEsXCS+0yx5DaMkHJ8HSXPfqIbloEpw8nL+e/IBcm2PN7EeqJSdnoDfzAIJ9VNep
+OkuE6N36B9K
-----END CERTIFICATE-----
)EOF";
X509List cert(trustRoot);



SSD1306Brzo display(0x3c, 5, 4); // Initialize OLED display

int blueLed = LED_BUILTIN; // Blue LED is on GPIO 2 (LED_BUILTIN)
int greenLed = 16; // Green LED is on GPIO 16

int analogPin = A0; // Analog input is A0
int analogValue = 0;

volatile byte state = LOW;
String button = "Waiting…";

void drawText() { // Fuction to draw the text
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Button: ");
  display.setFont(ArialMT_Plain_16);
  display.drawString(80, 10, button); // Print button press

  display.setFont(ArialMT_Plain_10);
  analogValue = analogRead(analogPin);
  display.drawString(0, 26, "ADC: " + String(analogValue)); // Print value of analog input

  display.drawString(0, 36,"IP : " + WiFi.localIP().toString());

}

void ICACHE_RAM_ATTR interrupt0() // Right
{
  button = "Right";
  blink();
}

void ICACHE_RAM_ATTR interrupt12() // Down
{
  button = "Down";
  blink();
}

void ICACHE_RAM_ATTR interrupt13() // Up
{
  button = "Up";
  blink();
}

void ICACHE_RAM_ATTR interrupt14() // Push
{
  button = "Push";
  blink();
}

void blink() {
  state = !state; // Reverse LED state
}

void httpsRequest();

void setup() {
   Serial.begin(115200);

  
  display.init(); // Initialise the display

  pinMode(blueLed, OUTPUT); // Initialize digital pin LED_BUILTIN as an output.
  pinMode(greenLed, OUTPUT); // initialize digital pin 16 as an output.

  pinMode(0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(0), interrupt0, FALLING); // Right
  pinMode(12, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(12), interrupt12, FALLING); // Down
  pinMode(13, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(13), interrupt13, FALLING); // Up
  pinMode(14, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(14), interrupt14, FALLING); // Push
  //interrupts();

  httpsRequest();
}

void loop() {
  display.clear(); // Clear OLED display
  drawText(); // Draw the text
  display.display(); // Write the buffer to the display

  digitalWrite(blueLed, state); // Turn the blue LED on/off
  digitalWrite(greenLed, !state); // Turn the green LED on/off
}


void httpsRequest() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  display.clear();
  display.drawString(0,0,"IP : " + WiFi.localIP().toString());
  display.display();
  // Set time via NTP, as required for x.509 validation
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("Connecting to ");
  Serial.println(host);

  Serial.printf("Using certificate: %s\n", trustRoot);
  client.setTrustAnchors(&cert);

  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection failed");
    return;
  }

  String url = "/repos/esp8266/Arduino/commits/master/status";
  Serial.print("Requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("Request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("Headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("Reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("Closing connection");
}

