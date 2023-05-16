// C++ code
//
#include <LiquidCrystal.h>

byte dot[8] = {
	0b00010,
  	0b00101,
  	0b00010,
  	0b00000,
  	0b00000,
  	0b00000,
  	0b00000,
  	0b00000
};

int sensor = A5;
int button1 = A4;
int button2 = A3;

int rs = 12;
int en = 11;
int dArray[] = {5, 4, 3, 2};
LiquidCrystal lcd = LiquidCrystal(rs, en, 
                                 dArray[0],
                                 dArray[1],
                                 dArray[2],
                                 dArray[3]);

void setup(){
  lcd.createChar(1, dot);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(6, 0);
  lcd.print("START");
  Serial.println("Start");
  delay(2000);
}

float getTemperature(){
  int sensorValue = analogRead(sensor);
  float mV = sensorValue / 1023.0 * 5.0 * 1000;
  float deg = (mV - 500) / 10;
  return deg;
}

int time = 0;
float memory[100];
int flick = 0;

void loop(){
  bool button1Pressed = analogRead(button1) - 1013;
  Serial.println(button1Pressed);
  lcd.clear();
  lcd.setCursor(0, 0);
  if(button1Pressed && time > 100){
    lcd.print("Avarage Temp: ");
    float sum = 0;
    for(int i = 0 ; i < 100 ; i++){
      sum += memory[i];
    }
    lcd.setCursor(0,1);
    lcd.print(sum / 100);
    lcd.write(byte(1));
  	lcd.print("C");
    for(;;){
    	if(analogRead(button1) - 1013) break;
    }
    lcd.clear();
  }
  if(button1Pressed && time < 100){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You need");
    lcd.setCursor(0,1);
    lcd.print("more samples");
    delay(2000);
    lcd.clear();
  }
  time++;
  lcd.print(getTemperature());
  lcd.write(byte(1));
  lcd.print("C");
  memory[flick] = getTemperature();
  flick++;
  if(flick >= 100) flick = 0;
  delay(100);
}
  