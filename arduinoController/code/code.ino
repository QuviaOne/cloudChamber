int tempPin1 = A1;
int tempPin2 = A2;
int tempPin3 = A3;
int tempPin4 = A4;
int tempPin5 = A5;

int controlPin1 = 2;
int controlPin2 = 3;
int controlPin3 = 4;

const float tempConstant = 0.48828125;
const float frameRate = 1000000 / 30;

void setup()
{
  // initialize the digital pin as an output.
  pinMode(tempPin1, INPUT);
  pinMode(tempPin2, INPUT);
  pinMode(tempPin3, INPUT);
  pinMode(tempPin4, INPUT);
  pinMode(tempPin5, INPUT);

  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(controlPin3, OUTPUT);

  digitalWrite(controlPin1, HIGH);
  digitalWrite(controlPin2, HIGH);
  digitalWrite(controlPin3, HIGH);

  Serial.begin(9600);
}

inline float readTempF(short id)
{
  if (id == 1)
  {
    return (analogRead(tempPin1) * tempConstant);
  }
  if (id == 2)
  {
    return (analogRead(tempPin2) * tempConstant);
  }
  if (id == 3)
  {
    return (analogRead(tempPin3) * tempConstant);
  }
  if (id == 4)
  {
    return (analogRead(tempPin4) * tempConstant);
  }
  if (id == 5)
  {
    return (analogRead(tempPin5) * tempConstant);
  }
  return (0);
}

inline float readTempC(short id)
{
  return (5 * (readTempF(id) - 32) / 9);
}

inline float readTempK(short id)
{
  return (readTempC(id) + 273.15);
}

void inline writeTemp(char unit)
{
  if (unit == 'f' or unit == 'F')
  {
    Serial.print("{\"id\": \"frame\", \"temps\": [");
    Serial.print(readTempF(1));
    Serial.print(",");
    Serial.print(readTempF(2));
    Serial.print(",");
    Serial.print(readTempF(3));
    Serial.print(",");
    Serial.print(readTempF(4));
    Serial.print(",");
    Serial.print(readTempF(5));
    Serial.print("]}");
    Serial.println("");
  }
  else if (unit == 'c' or unit == 'C')
  {
    Serial.print("{\"id\": \"frame\", \"temps\": [");
    Serial.print(readTempC(1));
    Serial.print(",");
    Serial.print(readTempC(2));
    Serial.print(",");
    Serial.print(readTempC(3));
    Serial.print(",");
    Serial.print(readTempC(4));
    Serial.print(",");
    Serial.print(readTempC(5));
    Serial.print("]}");
    Serial.println("");
  }
  else if (unit == 'k' or unit == 'K')
  {
    Serial.print("{\"id\": \"frame\", \"temps\": [");
    Serial.print(readTempK(1));
    Serial.print(",");
    Serial.print(readTempK(2));
    Serial.print(",");
    Serial.print(readTempK(3));
    Serial.print(",");
    Serial.print(readTempK(4));
    Serial.print(",");
    Serial.print(readTempK(5));
    Serial.print("]}");
    Serial.println("");
  }
}

long frames = micros() / frameRate;
void inline runFixedFrameRateLoop()
{
  if ((micros() / frameRate) - frames >= 1)
  {
    fixedFrameRateLoop(micros() - frames * frameRate);
    frames = round(micros() / frameRate)
  }
}



void inline fixedFrameRateLoop(int sinceLast)
{
  writeTemp('C');
}
void loop()
{
  runFixedFrameRateLoop();
}
