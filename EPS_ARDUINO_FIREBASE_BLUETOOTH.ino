#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <EEPROM.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define USER_EMAIL "pmk@gmail.com"
#define USER_PASSWORD "123Abc@@"

// Insert your network credentials
// #define WIFI_SSID "BB_624"
// #define WIFI_PASSWORD "Kuddus Ali"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDV9b5cGBbr4xe77iOBFaystConmEvRuwM"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://pc-control-a7861-default-rtdb.firebaseio.com/"

//EEPROM
#define EEPROM_SIZE 256
int flash = 0;
String Flash_Data;
String SSID = "";
String Password = "";
String Token = "";
int count_EP = 0;

int pin2 = 2;
int pin4 = 4;
int pin19 =19;

//Define Firebase Data object
FirebaseData database;

FirebaseAuth auth;
FirebaseConfig config;


// path for the two directories
String enterPasswordPath = "";
String statusPath = "";
String userNamePath = "";

bool enterPassword = false;
String status = "";


int cnt = 5;
String userID = "-NSEPuwbKZ8DA7IwVWTE";  // will get from bluetooth
String userName = "";                    // will get from Database
String pcPassword = "";
String pcPasswordPath = "";

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;



void setWifiPassword() {
  SSID = "";
  Token = "";
  Password = "";
  if (Serial.available()) {
    // Serial.write(SerialBT.read());
    // Serial.print(SerialBT.read());
    Flash_Data = Serial.readString();
    // EEPROM.writeString(1,Password);
    // EEPROM.commit();
    EEPROM.writeString(0, Flash_Data);
    // EEPROM.writeString(50,"SSID");
    // EEPROM.writeString(100,"PASSWORD");
    Serial.println(Flash_Data.length());
    EEPROM.commit();
    count_EP = 0;
    // Serial.println(Password);
    Serial.println("Password saved");
    // updateData(Flash_Data);

    for (int i = 0; i < Flash_Data.length(); i++) {
      if (Flash_Data[i] == '#') {
        count_EP = count_EP + 1;
        i++;
      }
      if (count_EP == 0) {
        SSID = SSID + String(Flash_Data[i]);
      }
      if (count_EP == 1) {
        Password = Password + String(Flash_Data[i]);
      }

      if (count_EP == 2 && Flash_Data[i] != ' ') {
        Token = Token + String(Flash_Data[i]);
      }
      if (count_EP > 2) { break; }
    }
    count_EP = 0;
    flash = 1;
  }

  if (flash == 1) {
    EEPROM.writeString(50, SSID);
    EEPROM.writeString(100, Password);
    EEPROM.writeString(150, Token);
    EEPROM.write(220, 10);
    EEPROM.commit();
  }
  flash = 0;

  Serial.print("Flash   ");
  Serial.println(Flash_Data);

  Serial.print("SSID ");
  String s = EEPROM.readString(50);
  const char* ss = s.c_str();
  Serial.println(ss);

  Serial.print("Password ");
  Serial.println(EEPROM.readString(100));

  Serial.print("Token ");
  Serial.println(EEPROM.readString(150));
  userID = EEPROM.readString(150);


  // delay(2000);
}


void getUserName() {
  userNamePath = updateUserNamePath_div();
  FirebaseData db;

  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getString(&db, userNamePath)) {
      userName = db.to<String>();
      Serial.println("UserName : " + userName);
      Serial.println("PATH: " + db.dataPath());
      Serial.println("TYPE: " + db.dataType());
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + db.errorReason());
    }
  }
}

void getEnterPassword() {
  enterPasswordPath = updateEnterPasswordPath_div();
  FirebaseData db;
  Serial.println(pcPassword);
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getBool(&db, enterPasswordPath)) {
      enterPassword = db.to<bool>();
      Serial.println("enterPassword : " + String(enterPassword));
      Serial.println("PATH: " + db.dataPath());
      Serial.println("TYPE: " + db.dataType());
    } else {
      Serial.println("FAILED");
      Serial.println("Path : " + enterPasswordPath);
      Serial.println("REASON: " + db.errorReason());
    }
  }
  delay(1005);
  getPcPassword();
}

void setEnterPassword() {
  enterPasswordPath = updateEnterPasswordPath_div();
  FirebaseData db;

  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.setBool(&db, enterPasswordPath, false)) {
      Serial.println("enterPassword set");
      Serial.println("PATH: " + db.dataPath());
      Serial.println("TYPE: " + db.dataType());
      cnt = 1;
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + db.errorReason());
      cnt = 1;
    }
  }
}

void getPcPassword() {
  pcPasswordPath = updatePcPasswordPath_div();
  FirebaseData db;

  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getBool(&db, pcPasswordPath)) {
      pcPassword = db.to<String>();
      Serial.println("pcPassword: " + pcPassword);
      Serial.println("PATH: " + db.dataPath());
      Serial.println("TYPE: " + db.dataType());
    } else {
      Serial.println("FAILED");
      Serial.println("Path : " + pcPasswordPath);
      Serial.println("REASON: " + db.errorReason());
    }
  }
}

// void getStatus(){
//   statusPath = updateStatusPath_div();
//   FirebaseData db;

//   if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
//       sendDataPrevMillis = millis();
//       if (Firebase.RTDB.getString(&db, statusPath)){
//           status = db.to<bool>();
//           Serial.println("Status : " + status);
//           Serial.println("PATH: " + db.dataPath());
//           Serial.println("TYPE: " + db.dataType());
//       }
//       else {
//           Serial.println("FAILED");
//           Serial.println("REASON: " + db.errorReason());
//       }
//   }
// }

// void setStatus(){
//   statusPath = updateStatusPath_div();
//   FirebaseData db;

//   if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
//       sendDataPrevMillis = millis();
//       if (Firebase.RTDB.setString(&db, statusPath, "Done")){
//           Serial.println("Status set");
//           Serial.println("PATH: " + db.dataPath());
//           Serial.println("TYPE: " + db.dataType());
//           cnt = 2;
//       }
//       else {
//           Serial.println("FAILED");
//           Serial.println("REASON: " + db.errorReason());
//           cnt = 2;
//       }
//   }
// }

String updateEnterPasswordPath_div() {
  String ret = "Devices/" + userID + "/enterPassword";
  // Serial.println("Path : " + ret);
  return ret;
}
String updatePcPasswordPath_div() {
  String ret = "Devices/" + userID + "/pcPassword";
  // Serial.println("Path : " + ret);
  return ret;
}
String updateUserNamePath_div() {
  String ret = "Devices/" + userID + "/userName";
  return ret;
}

// String updateStatusPath_div(){
//     String ret = ("Devices/"+userID+"/status");
//     return ret;
// }

String updateEnterPasswordPath_user() {
  String ret = ("/Users/" + userName + "/enterPassword");
  return ret;
}
String updateUserNamePath_user() {
  String ret = ("/Users/" + userName + "/userName");
  return ret;
}

String updateStatusPath_user() {
  String ret = ("/Users/" + userName + "/status");
  return ret;
}

void setup() {
  EEPROM.begin(EEPROM_SIZE);
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);  //RX2 = GPIO16, TX2 = 17
  delay(1000);
  pinMode(pin19,OUTPUT);
  String ROM_ssid = EEPROM.readString(50);
  String ROM_password = EEPROM.readString(100);
  const char* ssid;
  ssid = ROM_ssid.c_str();
  const char* password;
  password = ROM_password.c_str();
  Serial.print("ssid ");
  Serial.println(ssid);

  Serial.print("password ");
  Serial.println(password);
  Serial.println("____________________________");

  WiFi.mode(WIFI_STA);  //Optional
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
    if (WiFi.status() == WL_CONNECTED) {
      digitalWrite(pin19,HIGH);
      Serial.println("<<<<<<<<<<<<<<<<<<<<<<<<<<Connected to " + ROM_ssid + " Network>>>>>>>>>>>>>>>>>>>>>>>");
      break;
    }
    else{
      Serial.println("Not Connected");
      digitalWrite(pin19,LOW);
    }
    if (millis() > 10000) {
      break;
    }
  }


  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\nErorr!!!", config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  pinMode(pin2, OUTPUT);
  pinMode(pin4, OUTPUT);
}

void loop() {
  setWifiPassword();
  getEnterPassword();
  delay(1005);
  if (enterPassword == true && cnt > 0) {
    Serial.println("Eurekkkaaaaa!!!!!!!!!!!!!!!!!!");
    Serial2.println(pcPassword);
    delay(1000);
    digitalWrite(pin4, HIGH);

    delay(1000);
    digitalWrite(pin2, HIGH);


    delay(1000);




    cnt = -1;
  }
  digitalWrite(pin4, LOW);
  delay(100);

  digitalWrite(pin2, LOW);
  delay(100);
  if (enterPassword) {
    setEnterPassword();
  }
}