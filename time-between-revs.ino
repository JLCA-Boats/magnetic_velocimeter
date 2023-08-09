#define HALL_PIN A3
#define WHEEL_RADIOUS 33.0
#define VOLTAGE_THRESHOLD 520

unsigned long peaks[2] = {0,0};

double calculateWheelSpeed() {
  double frequency = (double)(peaks[0] - peaks[1]) / (double)1000.0 ;
  double wheel_speed = (1 / frequency) * WHEEL_RADIOUS * 2.0 * 3.1416; // on cm/s
  return wheel_speed / 27.777; // pass from cm/s to km/h
}


void setup() {
  Serial.begin(9600);
}

void loop() {

  double voltage = analogRead(HALL_PIN);

  if(voltage > VOLTAGE_THRESHOLD){
    unsigned long now = millis();

    if (abs(now - peaks[0]) > 100) {
      peaks[1] = peaks[0];
      peaks[0] = now;
      
      Serial.println(calculateWheelSpeed());
    }

  }
}

