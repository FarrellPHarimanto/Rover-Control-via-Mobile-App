#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Servo.h>

#define FIREBASE_HOST "nodemcu-b8ced.firebaseio.com"
#define FIREBASE_AUTH "4Nx86ysU9DR7GPdJN84Bd0SdOWo9XuZCK7onMYJr"


const char *ssid1 = "candyxt";
const char *password1 = "candyxt123";

const char *ssid2 = "candyasus";
const char *password2 = "candyasus123";

#define servoPin D1
Servo servo;
int angle = 0;


#define TCP_MSS whatever
#define LWIP_IPV6 whatever
#define LWIP_FEATURES whatever
#define LWIP_OPEN_SRC whatever

void setup() {
  Serial.begin(9600);
  while (WiFi.status() != WL_CONNECTED) {
    mynetwork();
  }

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.println("Successfully Connected ");
 Firebase.setInt("angle",0);
 
   servo.attach(servoPin);
  servo.write(angle);
}
void mynetwork() {
  Serial.println("Searching WiFi.....");
  int networks = WiFi.scanNetworks();
  for (int i = 0; i < networks; ++i) {
    if (WiFi.SSID(i) == ssid1 ) {
      WiFi.begin(ssid1, password1);
      Serial.println("\nWiFi Found");
      delay(2000);
      Serial.println("Connecting Please Wait");
      break;
    }
    else if (WiFi.SSID(i) == ssid2) {
      WiFi.begin(ssid2, password2);
      Serial.println("\nWiFi Found");
      delay(2000);
      Serial.println("Connecting Please Wait");
      break;
    } else {
      Serial.println("Unable to Find Authenticated WiFi ");
    }
  }
  delay(8000);
}

int servoAngle;

void loop() {
  if (WiFi.status() == WL_DISCONNECTED) {
    Serial.println("WiFi Disconnected");
    setup();
  } else {
    Serial.println("Connected");
    servoAngle = Firebase.getInt("angle");
     servo.write(servoAngle);
  }
}
