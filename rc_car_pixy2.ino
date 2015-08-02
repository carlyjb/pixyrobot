#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;
int xMax = 319;
int yMax = 199;
int xMid = xMax/2;
int yMid = yMax/2;

void setup() 
{
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  stopWheels();
  
  Serial.begin(9600);
  Serial.print("Starting...\n");
}

void loop()
{
  Serial.print("Loop...\n");
  detectBlocks();
}

void detectBlocks()
{
  uint16_t blocks = pixy.getBlocks();
  for (int j=0; j<blocks; j++)
  {
    Serial.print(j + "\n");
    if (pixy.blocks[j].signature == 1 || pixy.blocks[j].signature == 2)
    {
      steer(pixy.blocks[j].x, pixy.blocks[j].y);
    }
  }
}

void steer(int x, int y)
{
  if(x < xMid)
  {
    turnSharpLeft(100);
  }
  if(x > xMid)
  {
     turnSharpRight(100);
  } 
}
  
//rc drive commands  
void driveForwards(int speed)
{
  speed = checkSpeed(speed);
  rightForwards(speed);
  leftForwards(speed);
}

void driveBackwards(int speed)
{
  speed = checkSpeed(speed);
  rightBackwards(speed);
  leftBackwards(speed);
}

void turnSharpRight(int speed)
{
  speed = checkSpeed(speed);
  rightBackwards(speed);
  leftForwards(speed);
}

void turnSharpLeft(int speed)
{
  speed = checkSpeed(speed);
  rightForwards(speed);
  leftBackwards(speed);
}

//individual wheel controls
void rightBackwards(int speed)
{
  digitalWrite(6, LOW);
  analogWrite(5, speed);
}

void rightForwards(int speed)
{
    digitalWrite(5, LOW);
    analogWrite(6, speed);
}

void leftBackwards(int speed)
{
    digitalWrite(11, LOW);
    analogWrite(10, speed);   
}

void leftForwards(int speed)
{
    digitalWrite(10, LOW);
    analogWrite(11, speed);
}

void stopWheels()
{
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}


//speed limiter
int checkSpeed(int speed)
{
  if (speed < 60)
  {  speed = 60;  }
  if(speed > 225)
  { speed = 225;  }
  return speed;
}
  
