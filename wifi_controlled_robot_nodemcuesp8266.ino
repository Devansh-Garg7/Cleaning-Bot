/* include library */
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
WiFiClient client;
/* defining server port */
ESP8266WebServer server(80);

/* Define WiFi Credentials */
const char* ssid = "Galaxy M14 5G";  
const char* password = "qwertyuiop";

String  data = "";
int robospeed = 1023;

/* Defining right and left motor pins */
int RMotor_1 = 0;/* Right Motor GPIO0(D3) */
int RMotor_2 = 2;/* Right Motor GPIO2(D4) */
int LMotor_1 = 13;/* Left Motor GPIO13(D7) */
int LMotor_2 = 15;/* Left Motor GPIO15(D8) */

/* Defining L298N enable pins */
int REnable = 14;/* Right Motor Enable Pin GPIO14(D5) */
int LEnable = 12;/* Right Motor Enable Pin GPIO12(D6)  */

void setup() {
  Serial.begin(9600);
  Serial.println("GPIO test!");
  /* Initialize Motor Control Pins as Output */
  pinMode(RMotor_1, OUTPUT);
  pinMode(RMotor_2, OUTPUT);
  pinMode(LMotor_1, OUTPUT);
  pinMode(LMotor_2, OUTPUT);
  /* Initialize Motor Enable Pins as Output */
  pinMode(REnable, OUTPUT);
  pinMode(LEnable, OUTPUT);

  /* Connectinf to WiFi */
  connectingToWiFi();

  server.on("/", handleRequest);
  server.onNotFound(handleRequest);

  /* Starting Server */
  server.begin();
  Serial.println("Server started");
}
void loop() {

  analogWrite(REnable, robospeed);
  analogWrite(LEnable, robospeed);

  /* Handling Request */
  server.handleClient();
  String data = server.arg("Key");
  Serial.println(data);

  /* Setting Speed */
  if ( server.hasArg("Speed") ) {
    int _speed = (server.arg("Speed").toInt());
    robospeed = _speed;
    Serial.println(robospeed);
  }

  if (data == "F") {
    move_forward(); /* If data F moves Forward */
  }
  else if (data == "B") {
    move_backward(); /* If data B moves Backward */
  }
  else if (data == "R") {
    turn_right(); /* If data R moves Turn Right */
  }
  else if (data == "L") {
    turn_left(); /* If data L moves Turn Left */
  }
  else if (data == "S") {
    move_stop(); /* If data S moves Stop Moving */
  }
}

void handleRequest() {
  if ( server.hasArg("Key") ) {
    Serial.println(server.arg("Key"));
  }
  if ( server.hasArg("Speed") ) {
    Serial.println(server.arg("Speed"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}


void connectingToWiFi() {
  delay(3000);
  WiFi.disconnect();
  delay(1000);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(1000);
    Serial.print("...");
  }
  Serial.println("Connected");
  Serial.println("Local IP is : ");
  Serial.print((WiFi.localIP().toString()));
  delay(5000);
}

/* Move Forward */
void move_forward() {
  digitalWrite(RMotor_1, LOW);
  digitalWrite(RMotor_2, HIGH);
  digitalWrite(LMotor_1, HIGH);
  digitalWrite(LMotor_2, LOW);
}

/* Move Backward */
void move_backward() {
  digitalWrite(RMotor_1, HIGH);
  digitalWrite(RMotor_2, LOW);
  digitalWrite(LMotor_1, LOW);
  digitalWrite(LMotor_2, HIGH);
}

/* Turn Right */
void turn_right() {
  digitalWrite(RMotor_1, LOW);
  digitalWrite(RMotor_2, HIGH);
  digitalWrite(LMotor_1, LOW);
  digitalWrite(LMotor_2, HIGH);
}

/* Turn Left */
void turn_left() {
  digitalWrite(RMotor_1, HIGH);
  digitalWrite(RMotor_2, LOW);
  digitalWrite(LMotor_1, HIGH);
  digitalWrite(LMotor_2, LOW);
}

/* Stop Move */
void move_stop() {
  digitalWrite(RMotor_1, LOW);
  digitalWrite(RMotor_2, LOW);
  digitalWrite(LMotor_1, LOW);
  digitalWrite(LMotor_2, LOW);
}
