#define Pin_Pneumatic1 13
#define Pin_Pneumatic2 12
#define Pin_Pneumatic3 11
#define Pin_Pneumatic4 10
#define Pin_Pneumatic5 9

#define Pin_Motor1F 8
#define Pin_Motor1B 7

#define Pin_Motor2F 6
#define Pin_Motor2B 5

#define Pin_SW1 4
#define Pin_SW2 A5
#define Pin_SW3 A4
#define Pin_SW4 A3

#define Pin_LimitSwitch1 A0
#define Pin_LimitSwitch2 A1
#define Pin_LimitSwitch3 A2
void setup() {
  pinMode(Pin_Pneumatic1, OUTPUT);
  pinMode(Pin_Pneumatic2, OUTPUT);
  pinMode(Pin_Pneumatic3, OUTPUT);
  pinMode(Pin_Pneumatic4, OUTPUT);
  pinMode(Pin_Pneumatic5, OUTPUT);

  pinMode(Pin_Motor1F, OUTPUT);
  pinMode(Pin_Motor1B, OUTPUT);
  pinMode(Pin_Motor2F, OUTPUT);
  pinMode(Pin_Motor2B, OUTPUT);

  pinMode(Pin_SW1, INPUT);
  pinMode(Pin_SW2, INPUT);
  pinMode(Pin_SW3, INPUT);
  pinMode(Pin_SW4, INPUT);

  pinMode(Pin_LimitSwitch1, INPUT);
  pinMode(Pin_LimitSwitch2, INPUT);
  pinMode(Pin_LimitSwitch3, INPUT);

  Serial.begin(115200);

  digitalWrite(Pin_Pneumatic1, 1); delay(100);
  digitalWrite(Pin_Pneumatic2, 1); delay(100);
  digitalWrite(Pin_Pneumatic3, 1); delay(100);
  digitalWrite(Pin_Pneumatic4, 1); delay(100);
  digitalWrite(Pin_Pneumatic5, 1); delay(100);

  digitalWrite(Pin_Pneumatic1, 0); delay(100);
  digitalWrite(Pin_Pneumatic2, 0); delay(100);
  digitalWrite(Pin_Pneumatic3, 0); delay(100);
  digitalWrite(Pin_Pneumatic4, 0); delay(100);
  digitalWrite(Pin_Pneumatic5, 0); delay(100);

  digitalWrite(Pin_Motor1F, 1);
  digitalWrite(Pin_Motor2F, 1); delay(3000);
  digitalWrite(Pin_Motor1F, 0);
  digitalWrite(Pin_Motor2F, 0);
  digitalWrite(Pin_Motor1B, 1);
  digitalWrite(Pin_Motor2B, 1); delay(3000);
  digitalWrite(Pin_Motor1B, 0);
  digitalWrite(Pin_Motor2B, 0);

}

void loop() {

  Serial.print(digitalRead(Pin_SW1)); Serial.print(" ");
  Serial.print(digitalRead(Pin_SW2)); Serial.print(" ");
  Serial.print(digitalRead(Pin_SW3)); Serial.print(" ");
  Serial.print(digitalRead(Pin_SW4)); Serial.print(" Limit ");
  Serial.print(digitalRead(Pin_LimitSwitch1)); Serial.print(" ");
  Serial.print(digitalRead(Pin_LimitSwitch2)); Serial.print(" ");
  Serial.println(digitalRead(Pin_LimitSwitch3));

  if (digitalRead(Pin_LimitSwitch1) == 0)
  {
    digitalWrite(Pin_Pneumatic1, 1);
    digitalWrite(Pin_Pneumatic2, 1);
    digitalWrite(Pin_Pneumatic3, 1);
    digitalWrite(Pin_Pneumatic4, 1);
    digitalWrite(Pin_Pneumatic5, 1);
  
  }
  else if (digitalRead(Pin_LimitSwitch2) == 0)
  {
    digitalWrite(Pin_Pneumatic2, 1);
  }
  else if (digitalRead(Pin_LimitSwitch3) == 0)
  {
    digitalWrite(Pin_Pneumatic3, 1);
  }
  else if (digitalRead(Pin_SW1) == 0)
  {
    digitalWrite(Pin_Motor1F, 1);
    digitalWrite(Pin_Motor2F, 1);
    digitalWrite(Pin_Motor1B, 0);
    digitalWrite(Pin_Motor2B, 0);
  }
  else if (digitalRead(Pin_SW2) == 0)
  {
    digitalWrite(Pin_Motor1F, 0);
    digitalWrite(Pin_Motor2F, 0);
    digitalWrite(Pin_Motor1B, 1);
    digitalWrite(Pin_Motor2B, 1);
  }
  else if (digitalRead(Pin_SW3) == 0)
  {
    digitalWrite(Pin_Pneumatic4, 1);
    
    digitalWrite(Pin_Motor1F, 0);
    digitalWrite(Pin_Motor2F, 0);
    digitalWrite(Pin_Motor1B, 0);
    digitalWrite(Pin_Motor2B, 0);
  }
  else if (digitalRead(Pin_SW4) == 0)
  {
    digitalWrite(Pin_Pneumatic5, 1);
  }
  else
  {

    digitalWrite(Pin_Pneumatic1, 0);
    digitalWrite(Pin_Pneumatic2, 0);
    digitalWrite(Pin_Pneumatic3, 0);
    digitalWrite(Pin_Pneumatic4, 0);
    digitalWrite(Pin_Pneumatic5, 0);

  }
  delay(100);
  // put your main code here, to run repeatedly:

}
