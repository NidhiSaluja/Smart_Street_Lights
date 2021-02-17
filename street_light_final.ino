const int n = 3;
int sensorMax = 0;
int sensorMin = 1023;
int avg;
int ldrstatus;
int led[n] = {10, 11, 6};
int LDR = A1;
int trigPin[n] = {2, 4, 8};
int echoPin[n] = {3, 5, 9};

int i;
int maxd = 40; // Maximum range needed
int mind = 0; // Minimum range needed
int dark;
long distance[n] = {0, 0, 0}, duration[n] = {0, 0, 0}; // Duration used to calculate distance

void setup() {
  Serial.begin (9600);
  for (i = 0; i < n; i++)
  {
    pinMode(led[i], OUTPUT);
    pinMode(trigPin[i], OUTPUT);
    pinMode(echoPin[i], INPUT);
  }
}

void loop()
{
  /* The following trigPin/echoPin cycle is used to determine the
    distance of the nearest object by bouncing soundwaves off of it. */

  /*for (int i = 0; i < 5000; i++)
    {
    ldrstatus=analogRead(LDR);

    if (ldrstatus > sensorMax)
    {
      sensorMax = ldrstatus;
    }

    // record the minimum sensor value
    if (ldrstatus < sensorMin)
    {
      sensorMin = ldrstatus;
    }
    delay(1);
    }

    avg = (sensorMax + sensorMin) / 2;
    Serial.println(avg);
    //Serial.println(ldrstatus);
    ldrstatus=analogRead(LDR);
    Serial.println(ldrstatus);
    if (ldrstatus > 600)

    {
    dark = 0;//black
    }
    else

    {
    dark = 1;//white
    }
  */
  ldrstatus = analogRead(LDR);
  //Serial.println(ldrstatus);
  //delay(1000);
  for (i = 0; i < n; i++)
  {
    digitalWrite(trigPin[i], LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin[i], HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin[i], LOW);
    duration[i] = pulseIn(echoPin[i], HIGH);

    //Calculate the distance (in cm) based on the speed of sound.
    distance[i] = (duration[i]) / 58.2;
    //Serial.println( "dis of 1" distance1);
    ////////////////////////////////////////////////////////
  }

  if (ldrstatus >= 590)
  {
    dark = 1;//dark
  }
  else
  {
    dark = 0;//bright
  }
  Serial.println(dark);
  if (dark == 1)
  {
    //digitalWrite(led[i], 0);
    for (i = 0; i < n; i++)
    {
      if (distance[i] >= mind && distance[i] <= maxd)
      {
        digitalWrite(led[i], 255);
      }
      else
      {
        analogWrite(led[i], 25);
      }
    }
  }
  else if (dark == 0)
  {
    for (i = 0; i < n; i++)
    {
      if (distance[i] >= mind && distance[i] <= maxd)
      {
        digitalWrite(led[i], 0);
      }
      else
      {
        digitalWrite(led[i], 0);
      }
    }
  }
}
