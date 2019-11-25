#define SENSOR_NUMBER 5

#define SPEED 100
#define BADSPLIT 450
#define GOODSPLIT 650


const int ledPin[5]={13,12,11,3,2};
const int leftMotor = 10;
const int leftMotorSpeed = SPEED;
const int leftCon1 = 9;
const int leftCon2 = 8;
const int rightMotor = 6;
const int rightMotorSpeed = SPEED;
const int rightCon1 = 5;
const int rightCon2 = 4;

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

    for(int i=0;i<5;i++)
  {
    pinMode(ledPin[i],OUTPUT);
  }
}
void fwd(int);
void lturn(int);
void rturn(int);
void tlturn(int);
void trturn(int);
//void trackLine();

void loop() 
{
  fwd(1000);  
  rturn(200);
  fwd(1000);
}

void fwd(int delayTime)
{
  analogWrite(leftMotor, SPEED-25);
  analogWrite(rightMotor, SPEED-25);
  digitalWrite(leftCon1, LOW);
  digitalWrite(leftCon2, HIGH);
  digitalWrite(rightCon1, HIGH);
  digitalWrite(rightCon2, LOW);\
  delay(delayTime);
}
void lturn(int delayTime)
{
  analogWrite(leftMotor, SPEED);
  analogWrite(rightMotor, SPEED);
  
  digitalWrite(leftCon1, HIGH);
  digitalWrite(leftCon2, LOW);
  digitalWrite(rightCon1, HIGH);
  digitalWrite(rightCon2, LOW);
   delay(delayTime);
}
void rturn(int delayTime)
{
  analogWrite(leftMotor, SPEED);
  analogWrite(rightMotor, SPEED);
  digitalWrite(leftCon1, LOW);
  digitalWrite(leftCon2, HIGH);
  digitalWrite(rightCon1, LOW);
  digitalWrite(rightCon2, HIGH);
   delay(delayTime);
}
void tlturn(int delayTime)
{
  analogWrite(leftMotor, SPEED);
  analogWrite(rightMotor, SPEED);
  
  digitalWrite(leftCon1, LOW);
  digitalWrite(leftCon2, LOW);
  digitalWrite(rightCon1, HIGH);
  digitalWrite(rightCon2, LOW);
   delay(delayTime);
}
void trturn(int delayTime)
{
  analogWrite(leftMotor, SPEED);
  analogWrite(rightMotor, SPEED);
  digitalWrite(leftCon1, LOW);
  digitalWrite(leftCon2, HIGH);
  digitalWrite(rightCon1, LOW);
  digitalWrite(rightCon2, LOW);
   delay(delayTime);
}
/*void trackLine()
{
  delay(100);
 /* Serial.print(analogRead(A0));
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
    digitalWrite(ledPin[0],HIGH);
  }
  else
  {
    digitalWrite(ledPin[0],LOW);
  }
  
  if (analogRead(A1) > GOODSPLIT)
  {
    sensorVal[1] = 1;
    digitalWrite(ledPin[1],HIGH);
  }
   else
  {
    digitalWrite(ledPin[1],LOW);
  }
  
  if (analogRead(A2) > GOODSPLIT)
  {
    sensorVal[2] = 1;
    digitalWrite(ledPin[2],HIGH);
  }
   else
  {
    digitalWrite(ledPin[2],LOW);
  }
  
  if (analogRead(A3) > GOODSPLIT)
  {
    sensorVal[3] = 1;
    digitalWrite(ledPin[3],HIGH);
  }
   else
  {
    digitalWrite(ledPin[3],LOW);
  }
  
  if (analogRead(A4) > BADSPLIT)
  {
    sensorVal[4] = 1;
    digitalWrite(ledPin[4],HIGH);
  }
   else
  {
    digitalWrite(ledPin[4],LOW);
  }
  //Control part
  if(sensorVal[3]==1 && sensorVal[4]==1 && sensorVal[0]==1)
  {
   rturn();
   delay(600); 
  }
  else if(sensorVal[4]==1 && sensorVal[0]==1 && sensorVal[1]==1)
  {
    lturn();
    delay(600);
  }
  else if((sensorVal[3]==0 && sensorVal[4]==1) && sensorVal[0]==0 && sensorVal[1]==0)
  {
    rturn();
    delay(300);
  }
  else if((sensorVal[3]==1 && sensorVal[4]==1) && sensorVal[0]==0 && sensorVal[1]==0)
  {
    rturn();
    delay(200);
  }
  else if((sensorVal[3]==1 && sensorVal[4]==0) && sensorVal[0]==0 && sensorVal[1]==0 && sensorVal[2]==0)
  {
    rturn();
    delay(100);
  }
  else if((sensorVal[3]==1 && sensorVal[4]==0) && sensorVal[0]==0 && sensorVal[1]==0 && sensorVal[2]==1)
  {
    rturn();
    delay(50);
  }
  else if(sensorVal[3]==0 && sensorVal[4]==0 && (sensorVal[0]==1 && sensorVal[1]==0))
  {
    lturn();
    delay(300);
  }
  else if(sensorVal[3]==0 && sensorVal[4]==0 && (sensorVal[0]==1 && sensorVal[1]==1))
  {
    lturn();
    delay(200);
  }
  else if(sensorVal[3]==0 && sensorVal[4]==0 && (sensorVal[0]==0 && sensorVal[1]==1) && sensorVal[2]==0)
  {
    lturn();
    delay(100);
  }
  else if(sensorVal[3]==0 && sensorVal[4]==0 && (sensorVal[0]==0 && sensorVal[1]==1) && sensorVal[2]==1)
  {
    lturn();
    delay(100);
  }
  else
  {
    fwd();
  }
}*/
