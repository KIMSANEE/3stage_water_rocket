#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;

File myFile;
Servo myservo1;

int pos = 0;
float valocity = 0;
float s1 = 0;
void setup() {
  Serial.begin(115200);
  myservo1.attach(6);
  
}

void loop() {
  
  survo();
}

void survo(){
  // float avg_altitude = 0;
  // float sum = 0;
  if(Serial.available()>0){
    char receivedData = Serial.read();
    switch (receivedData) {
      case 'a':
        sd_open();
        break;
      case 'b':
        sd_close();
        break;
      case 'd':
        sd_read();
        break;
      case 'e':
        SD.remove("test.txt");
        Serial.println("removed");
        break;
       case 'c':
        for(pos = 90; pos>=0; pos--){
          myservo1.write(pos);
          delay(5);
        }
        // for(int i=0; i<10; i++){
        // float altitude =  bmp.readAltitude(101130);
        // sum += altitude;
        // }
        // avg_altitude = sum/10;
        float altitude =  bmp.readAltitude(101130);
        float s2 = altitude;
        if(s1 == 0){
          valocity = 0;
        } else{
          valocity = s2 - s1;
        }
        s1 = altitude;
        char charBuffer1[20];
        char charBuffer2[20];
        dtostrf(altitude, 2, 2, charBuffer1);
        dtostrf(valocity, 2, 2, charBuffer2);
        const char* myString1 = charBuffer1;
        const char* myString2 = charBuffer2;
        sd_write(myString1, myString2);
        break;
      default:
        for(pos = 0; pos<=90; pos++){
          myservo1.write(pos);
          delay(5);
        }
        break;
      }
  }
}

void sd_open(){
  Serial.print("Initializing SD card...");
  
  if (!SD.begin(4)) { // SD카드 모듈을 초기화합니다.
    Serial.println("initialization failed!"); // SD카드 모듈 초기화에 실패하면 에러를 출력합니다.
    while (1);
  }
  Serial.println("initialization done.");

  myFile = SD.open("test.txt", FILE_WRITE);
  
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  } // 두 번째 인자가 있으면 쓰기모드입니다.
}

void sd_close(){
  myFile.close();
  Serial.println("close");
}

void sd_write(const char* str1, const char* str2){
  
  if (myFile) { // 파일이 정상적으로 열리면 파일에 문자를 작성(추가)합니다.
    Serial.print("Writing to test.txt...");
    myFile.seek(myFile.size());
    myFile.print("Altitude : ");
    myFile.print(str1);
    myFile.println("m");
    myFile.print("Valocity : ");
    myFile.print(str2);
    myFile.println("m/s");
  } else {
    // 파일이 열리지 않으면 에러를 출력합니다.
    Serial.println("error opening test.txt");
  }
}

void sd_read(){
  myFile = SD.open("test.txt");
  
  if (myFile) {
    Serial.println("test.txt:");

    // while문을 통해 파일을 EOF(End-Of-File)까지 읽습니다.
    while (myFile.available()) {
      Serial.write(myFile.read()); // 읽을 파일이 있다면 시리얼로 출력합니다.
    }
    myFile.close(); // 파일을 닫습니다.
  } else {
    // 파일이 열리지 않으면 에러를 출력합니다.
    Serial.println("error opening test.txt");
  }
}
