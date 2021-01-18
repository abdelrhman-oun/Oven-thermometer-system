#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int temp, average, num_reads = 0, i = 0, buzzer = 10;
float sensor_val, x;
int arr_temp[60] = {0};
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 16);
  lcd.print("Temp.=");
  lcd.setCursor(13, 0);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Average=");
  lcd.setCursor(13, 1);
  lcd.print("C");
}

void loop() {
  delay(900);
  sensor_val = analogRead(A0);
  x = sensor_val * (5.0 / 1023.0);
  if (x <= 2.77) temp = ((x - 2.808)*(110 - 150) / (2.689 - 2.808)) + 150;
  else if (x < 3.01 && x > 2.77) temp = ((x - 3.016)*(160 - 200) / (2.844 - 3.016)) + 200;
  else if (x <= 3.23 && x >= 3.01) temp =((x - 3.289)*(210 - 250) / (3.066 - 3.289)) + 250;
  else if (x < 3.62 && x > 3.23) temp = ((x - 3.626)*(260 - 300) / (3.352 - 3.626)) + 300;
  else if (x >= 3.62) temp = ((x - 4.025)*(310 - 350) / (3.701 - 4.025)) + 350;
  lcd.setCursor(9, 0);
  lcd.print(temp);
  if(temp > 350){
    tone(buzzer, 500);
  }
  else noTone(buzzer);
  arr_temp[i] = temp;
  i++;
  if(i==60)i=0;
  if(num_reads < 61)num_reads++;
  average = 0;
  for(int j=0; j<=59; j++)average += arr_temp[j];
  average = average/num_reads;
  lcd.setCursor(9, 1);
  lcd.print(average);
}
