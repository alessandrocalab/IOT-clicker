#include <WiFi.h>
#include <ESP32Servo.h>
String deviceName = "SERVO-1";

WiFi.softAP("SERVO-SETUP")

const char* ssid = 
const char* password = 

WiFiServer server(80);

Servo mioServo;
int pinServo = 13;

void setup() {
  Serial.begin(115200);

  // Servo
  mioServo.setPeriodHertz(50);
  mioServo.attach(pinServo, 500, 2400);
  mioServo.write(90);

  // Connessione WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connessione WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnesso!");
  Serial.println(WiFi.localIP());

  server.begin();
}

IPAddress masterIP;
bool masterFound = false;

void findMaster() {
  WiFiClient c;
  if (c.connect("192.168.1.52", 9090)) {
    c.println(deviceName);     // manda il nome
    String r = c.readString();
    if (r.indexOf("OK") >= 0) {
      masterIP = c.remoteIP();
      masterFound = true;
      Serial.println("Registrato presso il master");
    }
    c.stop();
  }
}


unsigned long lastTry = 0;

void loop() {

  // 1) Tentativo di discovery ogni 2 secondi
  if (!masterFound && millis() - lastTry > 2000) {
    lastTry = millis();
    findMaster();
  }

  // 2) HTTP server sempre attivo
  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');

  // Se non abbiamo ancora un master → rifiuta tutto
  if (!masterFound) {
    client.stop();
    return;
  }

  // Controllo IP
  if (client.remoteIP().toString() != masterIP.toString()) {
    Serial.println("Connessione vietata");
    client.stop();
    return;
  }

  if (request.indexOf("pos=0") > 0)  mioServo.write(0);
  if (request.indexOf("pos=90") > 0) mioServo.write(90);
  if (request.indexOf("pos=180") > 0) mioServo.write(180);

  client.println("HTTP/1.1 200 OK");
  client.println();
  client.println("OK");
  client.stop();
}
