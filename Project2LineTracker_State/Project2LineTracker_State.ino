#define SENSOR_NUMBER 5

#define SPEED 85
#define BADSPLIT 450
#define GOODSPLIT 650


const int ledPin[5] = {13, 12, 11, 3, 2};
const int leftMotor = 10;
const int leftMotorSpeed = SPEED;
const int leftCon1 = 9;
const int leftCon2 = 8;
const int rightMotor = 6;
const int rightMotorSpeed = SPEED;
const int rightCon1 = 5;
const int rightCon2 = 4;
int state = 1;
void setup()
{
  Serial.begin(9600);
  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);
  pinMode(leftCon1, OUTPUT);
  pinMode(leftCon2, OUTPUT);
  pinMode(rightCon1, OUTPUT);
  pinMode(rightCon2, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);

  for (int i = 0; i < 5; i++)
  {
    pinMode(ledPin[i], OUTPUT);
  }
}
void fwd();
void lturn(int);
void rturn(int);
void stopp();

static int error = 0, prevError = 0, sumError = 0;
void loop()
{
  /*
    //delay(50);
    Serial.print(analogRead(A0));
    Serial.print(" ");
    Serial.print(analogRead(A1));
    Serial.print(" ");
    Serial.print(analogRead(A2));
    Serial.print(" ");
    Serial.print(analogRead(A3));
    Serial.print(" ");
    Serial.println(analogRead(A4));*/


  //Prepare easy-to-digest analogRead
  int sensorVal[5] = {}; //All are 0 by default
  if (analogRead(A0) > GOODSPLIT)
  {
    sensorVal[0] = 1;
    digitalWrite(ledPin[0], HIGH);
  }
  else
  {
    digitalWrite(ledPin[0], LOW);
  }

  if (analogRead(A1) > GOODSPLIT)
  {
    sensorVal[1] = 1;
    digitalWrite(ledPin[1], HIGH);
  }
  else
  {
    digitalWrite(ledPin[1], LOW);
  }

  if (analogRead(A2) > GOODSPLIT)
  {
    sensorVal[2] = 1;
    digitalWrite(ledPin[2], HIGH);
  }
  else
  {
    digitalWrite(ledPin[2], LOW);
  }

  if (analogRead(A3) > GOODSPLIT)
  {
    sensorVal[3] = 1;
    digitalWrite(ledPin[3], HIGH);
  }
  else
  {
    digitalWrite(ledPin[3], LOW);
  }

  if (analogRead(A4) > BADSPLIT)
  {
    sensorVal[4] = 1;
    digitalWrite(ledPin[4], HIGH);
  }
  else
  {
    digitalWrite(ledPin[4], LOW);
  }

  //Control part
  //1st state
  if (state == 1)
  {
    if (sensorVal[0] == 1 && sensorVal[1] == 0 && sensorVal[3] == 0 && sensorVal[4] == 0)
    {
      lturn(70);
    }
    else if (sensorVal[0] == 1 && sensorVal[1] == 1 && sensorVal[3] == 0 && sensorVal[4] == 0)
    {
      lturn(50);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 1 && sensorVal[3] == 0 && sensorVal[4] == 0)
    {
      lturn(30);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[3] == 0 && sensorVal[4] == 1)
    {
      rturn(70);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[3] == 1 && sensorVal[4] == 1)
    {
      rturn(50);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[3] == 1 && sensorVal[4] == 0)
    {
      rturn(30);
    }
    else if (sensorVal[0] == 1 && sensorVal[1] == 1 && sensorVal[3] == 1 && sensorVal[4] == 1)
    {
      lturn(50);
      delay(200);
    }
    else if(sensorVal[0]+sensorVal[1]>sensorVal[3]+sensorVal[4])
    {
      lturn(40);
    }
    else if(sensorVal[0]+sensorVal[1]<sensorVal[3]+sensorVal[4])
    {
      rturn(40);
      delay(200);    }
    else
    {
      fwd();
    }
  }

  //2nd state
  if (state==2)
  {
    if (sensorVal[0] == 1 && sensorVal[1] == 0 && sensorVal[3] == 0 && sensorVal[4] == 0)
    {
      lturn(70);
    }
    else if (sensorVal[0] == 1 && sensorVal[1] == 1 && sensorVal[3] == 0 && sensorVal[4] == 0)
    {
      lturn(50);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 1 && sensorVal[3] == 0 && sensorVal[4] == 0)
    {
      lturn(30);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[3] == 0 && sensorVal[4] == 1)
    {
      rturn(70);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[3] == 1 && sensorVal[4] == 1)
    {
      rturn(50);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[3] == 1 && sensorVal[4] == 0)
    {
      rturn(30);
    }
    else if (sensorVal[0] == 1 && sensorVal[1] == 1 && sensorVal[3] == 1 && sensorVal[4] == 1)
    {
      fwd();
      delay(300);
    }
    else if(sensorVal[0]+sensorVal[1]>sensorVal[3]+sensorVal[4])
    {
      lturn(40);
    }
    else if(sensorVal[0]+sensorVal[1]<sensorVal[3]+sensorVal[4])
    {
      rturn(40);
    }
    else
    {
      fwd();
    }
  }


  //3rd state
  if (state == 3)
  {
     if (sensorVal[0] == 1 && sensorVal[1] == 0 && sensorVal[3] == 0 && sensorVal[4] == 0)
    {
      lturn(70);
    }
    else if (sensorVal[0] == 1 && sensorVal[1] == 1 && sensorVal[3] == 0 && sensorVal[4] == 0)
    {
      lturn(50);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 1 && sensorVal[3] == 0 && sensorVal[4] == 0)
    {
      lturn(30);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[3] == 0 && sensorVal[4] == 1)
    {
      rturn(70);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[3] == 1 && sensorVal[4] == 1)
    {
      rturn(50);
      delay(400);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[3] == 1 && sensorVal[4] == 0)
    {
      rturn(30);
    }
    else if (sensorVal[0] == 1 && sensorVal[1] == 1 && sensorVal[3] == 1 && sensorVal[4] == 1)
    {
      lturn(50);
      delay(250);
    }
    else if(sensorVal[0]+sensorVal[1]>sensorVal[3]+sensorVal[4])
    {
      lturn(40);
    }
    else if(sensorVal[0]+sensorVal[1]<sensorVal[3]+sensorVal[4])
    {
      rturn(40);
    }
    else
    {
      fwd();
    }
  }


  //4th state
  if(state == 4)
  {
     if (sensorVal[0] == 1 && sensorVal[1] == 0 && sensorVal[3] == 0 && sensorVal[4] == 0)
    {
      lturn(70);
    }
    else if (sensorVal[0] == 1 && sensorVal[1] == 1 && sensorVal[3] == 0 && sensorVal[4] == 0)
    {
      lturn(50);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 1 && sensorVal[3] == 0 && sensorVal[4] == 0)
    {
      lturn(30);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[3] == 0 && sensorVal[4] == 1)
    {
      rturn(70);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[3] == 1 && sensorVal[4] == 1)
    {
      rturn(50);
    }
    else if (sensorVal[0] == 0 && sensorVal[1] == 0 && sensorVal[3] == 1 && sensorVal[4] == 0)
    {
      rturn(30);
    }
    else if (sensorVal[0] == 1 && sensorVal[1] == 1 && sensorVal[3] == 1 && sensorVal[4] == 1)
    {
      lturn(50);
      delay(300);
    }
    else if(sensorVal[0]+sensorVal[1]>sensorVal[3]+sensorVal[4])
    {
      lturn(40);
    }
    else if(sensorVal[0]+sensorVal[1]<sensorVal[3]+sensorVal[4])
    {
      rturn(40);
    }
    else
    {
      fwd();
    }
  }
}



void fwd()
{
  analogWrite(leftMotor, SPEED);
  analogWrite(rightMotor, SPEED);
  digitalWrite(leftCon1, LOW);
  digitalWrite(leftCon2, HIGH);
  digitalWrite(rightCon1, HIGH);
  digitalWrite(rightCon2, LOW);
}
void lturn(int moreSpd)
{
  analogWrite(leftMotor, SPEED + moreSpd);
  analogWrite(rightMotor, SPEED + moreSpd);

  digitalWrite(leftCon1, HIGH);
  digitalWrite(leftCon2, LOW);
  digitalWrite(rightCon1, HIGH);
  digitalWrite(rightCon2, LOW);
}
void rturn(int moreSpd)
{
  analogWrite(leftMotor, SPEED + moreSpd);
  analogWrite(rightMotor, SPEED + moreSpd);
  digitalWrite(leftCon1, LOW);
  digitalWrite(leftCon2, HIGH);
  digitalWrite(rightCon1, LOW);
  digitalWrite(rightCon2, HIGH);
}

void stopp()
{
  analogWrite(leftMotor, 0);
  analogWrite(rightMotor, 0);
  digitalWrite(leftCon1, LOW);
  digitalWrite(leftCon2, LOW);
  digitalWrite(rightCon1, LOW);
  digitalWrite(rightCon2, LOW);
}
