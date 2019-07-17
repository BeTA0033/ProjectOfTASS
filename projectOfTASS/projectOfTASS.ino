#include <Servo.h>

Servo myservo;

#define nem_sensoru1 A0 /*analog tanimlanan birinci nem sensoru*/
#define nem_sensoru2 A1 /*analog tanimlanan ikinci nem sensoru*/
#define yagmur_sensoru A2 /*analog tanimlanan yagmur sensoru*/
#define motor_pin 9 /*tanimlanan motorun pini*/
#define kirmizi_led_pin 10 /*sulama sistemindeki hatayi haber verecek led*/
#define calisma_siniri 600

int pos = 0;/*servonun baslangic pozisyonu*/
int nem_degeri1 = 0;
int nem_degeri2 = 0;
int yagmur_degeri = 0;
/*nem ve yagmur degerleri sifira esitlendi(baslangic degerleri icin)*/
 
void setup(){
  pinMode(motor_pin , OUTPUT);
  pinMode(kirmizi_led_pin , OUTPUT);
  myservo.attach(11);
  Serial.begin(9600);
}

void loop(){
nem_degeri1 = analogRead(nem_sensoru1);
nem_degeri2 = analogRead(nem_sensoru2);
yagmur_degeri=analogRead(yagmur_sensoru);

  if(yagmur_degeri<calisma_siniri)//hava yagmurlu ise
  {
    Serial.println("Yagmur Yagiyor...");
    Serial.println(yagmur_degeri);
    digitalWrite(motor_pin, LOW);
    delay(1000);
  }
  else//hava yagmurlu degil ise
  {
   nem_degeri1 = analogRead(nem_sensoru1);
   Serial.println("\nArea 1 = ");
   Serial.println(nem_degeri1);
   delay(1000);
   
   nem_degeri2 = analogRead(nem_sensoru2);
   Serial.println("\nArea 2 = "); 
   Serial.println(nem_degeri2);
   delay(1000);
   
    if(nem_degeri1 <= nem_degeri2)
    {
       if (nem_degeri1 > calisma_siniri)//birinci bolge
       {  
          servo1();  
          digitalWrite(motor_pin, HIGH);
          digitalWrite(kirmizi_led_pin, HIGH);
          delay(3000);
          digitalWrite(kirmizi_led_pin, LOW);    
          digitalWrite(motor_pin, LOW);    
          delay(5000);
       }
       else
       {      
          digitalWrite(motor_pin, LOW);    
       }
    }
    else if(nem_degeri2 < nem_degeri1)//ikinci bolge
    {
       if (nem_degeri1 > calisma_siniri)
       {    
          servo2();
          digitalWrite(motor_pin, HIGH);
          digitalWrite(kirmizi_led_pin, HIGH);
          delay(3000);
          digitalWrite(kirmizi_led_pin, LOW);    
          digitalWrite(motor_pin, LOW);    
          delay(5000);
       }
       else
       {      
          digitalWrite(motor_pin, LOW);    
       }
    }
    else//aksi durumlarda
    {
      digitalWrite(motor_pin, LOW);    
      delay(1000);
    }
}
}

void servo1()
{
  for (pos = 0; pos <= 120; pos += 10)
  {
    myservo.write(pos);
    delay(15);             
  }
}

void servo2()
{
  for (pos = 120; pos >= 0; pos -= 10)
  {
    myservo.write(pos);
    delay(15);             
  }
}
