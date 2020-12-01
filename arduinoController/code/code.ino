int tempPin1 = A1;
int tempPin2 = A2;
int tempPin3 = A3;
int tempPin4 = A4;
int tempPin5 = A5;

float val = 0;
float frameRate = 1000000/30;

void setup() {                
  // initialize the digital pin as an output.
  pinMode(tempPin1, INPUT);
  pinMode(tempPin2, INPUT); 
  pinMode(tempPin3, INPUT); 
  pinMode(tempPin4, INPUT); 
  pinMode(tempPin5, INPUT); 
  
  Serial.begin(9600);
}

void loop() {
  unsigned long start = micros();
 
  val = analogRead(analogR);
  float temp = val*0.48828125;
  float tempC = 5*(temp - 32)/9;

  Serial.print(temp);
  Serial.print("    ");
  Serial.println(tempC);

  while (micros()-start <= frameRate && micros()-start >= 0){}
}

float[] inline readTempF(){
    
}

float[] inline readTempC(){

}
