// Robotics with the BOE Shield - Circumference

void setup()
{
  Serial.begin(9600);

  float r = 0.75;
  float c = 2.0 * PI * r;
  float area = PI * r*r;
 
  Serial.print("circumference = ");
  Serial.println(c);
  Serial.print("Area = ");
  Serial.println(area);
}

void loop()
{
  // Empty, no repeating code.
}
