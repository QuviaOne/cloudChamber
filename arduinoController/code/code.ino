int tempPin1 = A1;
int tempPin2 = A2;
int tempPin3 = A3;
int tempPin4 = A4;
int tempPin5 = A5;

bool cP1 = false;
bool cP2 = false;
bool cP3 = false;
int controlPin1 = 2;
int controlPin2 = 3;
int controlPin3 = 4;

const float tempConstant = 0.48828125;
const float frameRate = 1000000 / 30;

//TEMPRATURE CORRECTION CONSTANTS
const float sensor1CorrectionalConstant = 10;
const float sensor2CorrectionalConstant = 7;
const float sensor3CorrectionalConstant = 7;
const float sensor4CorrectionalConstant = 7;
const float sensor5CorrectionalConstant = 7;

inline void updateOutPins(){
  if (cP1){
    digitalWrite(controlPin1, HIGH);
  }
  else{
    digitalWrite(controlPin1, LOW);
  }
  if (cP2){
    digitalWrite(controlPin2, HIGH);
  }
  else{
    digitalWrite(controlPin2, LOW);
  }
  if (cP3){
    digitalWrite(controlPin3, HIGH);
  }
  else{
    digitalWrite(controlPin3, LOW);
  }
}

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

  updateOutPins();

  Serial.begin(115200);

  Serial.println("reset");
}

inline float readTempF(short id)
{
  if (id == 1)
  {
    return (analogRead(tempPin1) * tempConstant + sensor1CorrectionalConstant);
  }
  if (id == 2)
  {
    return (analogRead(tempPin2) * tempConstant + sensor2CorrectionalConstant);
  }
  if (id == 3)
  {
    return (analogRead(tempPin3) * tempConstant + sensor3CorrectionalConstant);
  }
  if (id == 4)
  {
    return (analogRead(tempPin4) * tempConstant + sensor4CorrectionalConstant);
  }
  if (id == 5)
  {
    return (analogRead(tempPin5) * tempConstant) + sensor5CorrectionalConstant;
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

void inline fixedFrameRateLoop(int sinceLast)
{
  writeTemp('C');
}

long frames = micros() / frameRate;
void inline runFixedFrameRateLoop()
{
  if ((micros() / frameRate) - frames >= 1)
  {
    fixedFrameRateLoop(micros() - frames * frameRate);
    frames = round(micros() / frameRate);
  }
}
void loop()
{
   if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    if (data == "_1"){
      cP1 = !cP1;
    }
    else if (data == "_2"){
      cP2 = !cP2;
    }
    else if (data == "_3"){
      cP3 = !cP3;
    }
    updateOutPins();
  }
  runFixedFrameRateLoop();
}
