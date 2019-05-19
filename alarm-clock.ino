#include "application.h"

Application app;

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  app.init();
}

void loop()
{
  app.update();
}
