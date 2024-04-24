#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;
int SW = 10;
int once1 = 0;
int once2 = 0;
float valocity = 0;
float s1 = 0;
float s2 = 0;

File myFile;
Servo myservo1;

void setup() {
  Serial.begin(115200);// put your setup code here, to run once:
  myservo1.attach(6);
}

void loop() {
  int switchState = digitalRead(SW);
  if(switchState == HIGH){
    if(once1 == 0){
    SD.remove("test.txt");
    sd_open();
    once1 = 1;
    once2 = 0;
    } else{
      float sum = 0;
      for(int i=0; i<10; i++){
        float altitude =  bmp.readAltitude(101780);
        sum += altitude;
        delay(10);
      }
      float avg_altitude = sum/10;
      s2 = avg_altitude;
      if(s1 == 0){
        valocity = 0;
      } else{
        valocity = s2 - s1;
      }
      s1 = avg_altitude;
      char charBuffer1[20];
      char charBuffer2[20];
      dtostrf(avg_altitude, 2, 2, charBuffer1);
      dtostrf(valocity, 2, 2, charBuffer2);
      const char* myString1 = charBuffer1;
      const char* myString2 = charBuffer2;
      sd_write(myString1, myString2);
    } 
    } else{
      if(once2 ==0){
      sd_close();
      delay(1000);
      myservo1.write(120);
      sd_read();
      once2 = 1;
      once1 = 0;
      } else {
        delay(2000);
        myservo1.write(0);
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
