#define SENSOR_NUMBER 5
#define MOTOR_MAXSPEED 250
#define MOTOR_BASESPEED 155
#define BADSPLIT 500
#define GOODSPLIT 720


const int ledPin[5]={13,12,11,3,2};

const int leftMotor = 10, leftMotorSpeed = MOTOR_BASESPEED, leftCon1 = 9, leftCon2 = 8;
const int rightMotor = 6, rightMotorSpeed = MOTOR_BASESPEED, rightCon1 = 5, rightCon2 = 4;

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


  analogWrite(leftMotor,MOTOR_BASESPEED);
  analogWrite(rightMotor,MOTOR_BASESPEED);
  digitalWrite(leftCon1, LOW);
    digitalWrite(leftCon2, HIGH);
    digitalWrite(rightCon1, LOW);
    digitalWrite(rightCon2, HIGH);
}
void fd();
void lturn();
void rturn();
void motorSpeedControl(int error, int prevError, int sumError);

static int error = 0, prevError = 0, sumError = 0;
void loop()
{

  Serial.print(analogRead(A0));
  Serial.print(" ");
  Serial.print(analogRead(A1));
  Serial.print(" ");
  Serial.print(analogRead(A2));
  Serial.print(" ");
  Serial.print(analogRead(A3));
  Serial.print(" ");
  Serial.println(analogRead(A4));


  //Prepare easy-to-digest analogRead
  bool sensorVal[5] = {}; //All are 0 by default
  if (analogRead(A0) > BADSPLIT)
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
  
  if (analogRead(A4) > GOODSPLIT)
  {
    sensorVal[4] = 1;
    digitalWrite(ledPin[4],HIGH);
  }
   else
  {
    digitalWrite(ledPin[4],LOW);
  }

  int binSensorVal = 0;
  binSensorVal = sensorVal[0] + sensorVal[1] * 2 + sensorVal[2] * 4 + sensorVal[3] * 8 + sensorVal[4] * 16;
  //Serial.println(binSensorVal);

  //Assign Error Value
  /* Possible analogRead in BIN
    10000 -> 16
    11000 -> 24
    01000 -> 8
    01100 -> 12
    00100 -> 4
    00110 -> 6
    00010 -> 2
    00011 -> 3
    00001 -> 1
  */
  switch (binSensorVal)
  {
    case 16: error = 4; break;
    case 24: error = 3; break;
    case 8: error = 2; break;
    case 12: error = 1; break;
    case 4 : error = 0; break;
    case 6: error = -1; break;
    case 2: error = -2; break;
    case 3: error = -3; break;
    case 1: error = -4; break;
    default: error = 0; break;
  }

  //PID
  motorSpeedControl(error, prevError, sumError);
  prevError = error;
  sumError += error;
  Serial.println(error);
  delay(250);
}

void motorSpeedControl(int error, int prevError, int sumError)
{
  const int Kp = 20, Kd = 5, Ki = 5;
  int deltaSpeed = Kp * error + Kd * (error - prevError) + Ki * sumError;

  //PWM MOTOR SPEED
  int rSpeed = MOTOR_BASESPEED + deltaSpeed, lSpeed = MOTOR_BASESPEED - deltaSpeed;

  analogWrite(leftMotor, abs(lSpeed));
  analogWrite(rightMotor, abs(rSpeed));
  if (lSpeed >= 0)
  {
    digitalWrite(leftCon1, LOW);
    digitalWrite(leftCon2, HIGH);
  }
  else
  {
    digitalWrite(leftCon2, LOW);
    digitalWrite(leftCon1, HIGH);
  }

  if (rSpeed >= 0)
  {
    digitalWrite(rightCon1, LOW);
    digitalWrite(rightCon2, HIGH);
  }
  else
  {
    digitalWrite(rightCon2, LOW);
    digitalWrite(rightCon1, HIGH);
  }



}


void fd()
{
  analogWrite(leftMotor, MOTOR_BASESPEED);
  analogWrite(rightMotor, MOTOR_BASESPEED);
  digitalWrite(leftCon1, HIGH);
  digitalWrite(rightMotor, HIGH);
  digitalWrite(leftCon1, HIGH);
  digitalWrite(leftCon2, LOW);
  digitalWrite(rightCon1, LOW);
  digitalWrite(rightCon2, HIGH);
}
void lturn()
{
  analogWrite(leftMotor, MOTOR_BASESPEED);
  analogWrite(rightMotor, 2 * MOTOR_BASESPEED);
  digitalWrite(leftMotor, HIGH);
  digitalWrite(rightMotor, HIGH);
  digitalWrite(leftCon1, HIGH);
  digitalWrite(leftCon2, LOW);
  digitalWrite(rightCon1, LOW);
  digitalWrite(rightCon2, HIGH);
}
void rturn()
{
  analogWrite(leftMotor, 2 * MOTOR_BASESPEED);
  analogWrite(rightMotor, MOTOR_BASESPEED);
  digitalWrite(leftMotor, HIGH);
  digitalWrite(rightMotor, HIGH);
  digitalWrite(leftCon1, HIGH);
  digitalWrite(leftCon2, LOW);
  digitalWrite(rightCon1, LOW);
  digitalWrite(rightCon2, HIGH);
}
