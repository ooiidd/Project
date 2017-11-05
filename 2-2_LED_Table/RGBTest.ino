int redPin = 10;

int greenPin = 9;

int bluePin = 8;

 

void setup()

{

 pinMode(redPin, OUTPUT);

 pinMode(greenPin, OUTPUT);
  shiftOut(8,10,LSBFIRST,B11011011);
  digitalWrite(greenPin,HIGH);
 pinMode(bluePin, OUTPUT); 
   shiftOut(8,10,LSBFIRST,B11011011);

}

 

void loop()

{
  delay(1000);
  shiftOut(8,10,LSBFIRST,B11011011);
    shiftOut(8,10,LSBFIRST,B11011011);
      shiftOut(8,10,LSBFIRST,B11011011);

        delay(1000);
}

 

void setColor(int red, int green, int blue)

{

  analogWrite(redPin, 255-red);

  analogWrite(greenPin, 255-green);

  analogWrite(bluePin, 255-blue); 

}

