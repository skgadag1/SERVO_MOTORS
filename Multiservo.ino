#include <SoftwareSerial.h>
#include <Servo.h> 
Servo s1, s2, s3, s4;
int dl1=2, dr1=4, dl2=9, dr2=12;

int bluetoothTx = 7;
int bluetoothRx = 8;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  s1.attach(5);
  s2.attach(6);
  s3.attach(10);
  s4.attach(11);
  pinMode(dl1, OUTPUT);
  pinMode(dl2, OUTPUT);
  pinMode(dr1, OUTPUT);
  pinMode(dr2, OUTPUT);
  Serial.begin(9600);
  bluetooth.begin(38400);
}

void loop()
{
  if(bluetooth.available()>=2)
    servo();
  if(bluetooth.available()==1)
    dcm();
}

void servo()
{
    unsigned int servopos = bluetooth.read();
    unsigned int servopos1 = bluetooth.read();
    unsigned int realservo = (servopos1 *256) + servopos; 
    Serial.println(realservo); 
    
    if (realservo >= 1000 && realservo <1045)
    {
    int servo1 = realservo;
    servo1 = map(servo1, 1000,1045,135,180);
    s1.write(servo1);
    Serial.println("servo 1 ON");
    delay(10);
    }
    
    if (realservo >=2000 && realservo <2045)
    {
      int servo2 = realservo;
      servo2 = map(servo2,2000,2045,135,180);
      s2.write(servo2);
      Serial.println("servo 2 On");
      delay(10);
    }
    
    if (realservo >=3000 && realservo < 3090)
    {
      int servo3 = realservo;
      servo3 = map(servo3, 3000, 3090,45,135);
      s3.write(servo3);
      Serial.println("servo 3 On");
      delay(10);
    }
    
    if (realservo >=4000 && realservo < 4090)
    {
      int servo4 = realservo;
      servo4 = map(servo4, 4000, 4090,45,135);
      s4.write(servo4);
      Serial.println("servo 4 On");
      delay(10);
    }
}

void dcm()
{
int br=bluetooth.read();    
if(br==10)
    {
      digitalWrite(dl2, LOW);
      digitalWrite(dr2, HIGH);
      
      delay(10);
      Serial.println("DC MOTOR_2 CLOCK_WISE");
    }
    else if(br==9)
    {
      digitalWrite(dl1, LOW);
      digitalWrite(dr1, HIGH);
      delay(10);
      Serial.println("DC MOTOR_1 CLOCK_WISE");
    }
    else if(br==8)
    {
      digitalWrite(dl1, HIGH);
      digitalWrite(dr1, LOW);
      
      delay(10);
      Serial.println("DC MOTOR_1 ANTI_CLOCK_WISE");
    }
    else if(br==13)
    {
      digitalWrite(dl2, HIGH);
      digitalWrite(dr2, LOW);
      
      delay(10);
      Serial.println("DC MOTOR_2 ANTI_CLOCK_WISE");
    }   
    else if(br==7)
    {
      digitalWrite(dl1, LOW);
      digitalWrite(dr1, LOW);
      digitalWrite(dl2, LOW);
      digitalWrite(dr2, LOW);
      
      delay(10);
      Serial.println("STOP");
    }
}
