/* Basic Digital Read
 * ------------------ 
 *
 * turns on and off a light emitting diode(LED) connected to digital  
 * pin 13, when pressing a pushbutton attached to pin 7. It illustrates the
 * concept of Active-Low, which consists in connecting buttons using a
 * 1K to 10K pull-up resistor.
 *
 * Created 1 December 2005
 * copyleft 2005 DojoDave <http://www.0j0.org>
 * http://arduino.berlios.de
 *
 */

#define ledPin 4 //the pin with the LED
#define RELAY1 5
#define speakerPin 9

#define BUTTON_PIN        7  // Button

#define LONGPRESS_LEN    25  // Min nr of loops for a long press
#define DELAY            200  // Delay per loop in ms

enum { EV_NONE=0, EV_SHORTPRESS, EV_LONGPRESS };

boolean button_was_pressed; // previous state
int button_pressed_counter; // press running duration

void setup()
{
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH); // pull-up
  Serial.begin(9600);
  button_was_pressed = false;
  button_pressed_counter = 0;
}

int handle_button()
{
  int event;
  int button_now_pressed = !digitalRead(BUTTON_PIN); // pin low -> pressed

  if (!button_now_pressed && button_was_pressed) {
    if (button_pressed_counter < LONGPRESS_LEN)
      event = EV_SHORTPRESS;
    else
      event = EV_LONGPRESS;
  }
  else
    event = EV_NONE;

  if (button_now_pressed)
    ++button_pressed_counter;
  else
    button_pressed_counter = 0;

  button_was_pressed = button_now_pressed;
  return event;
}

void loop()
{
  // handle button
  boolean event = handle_button();

  // do other things
  switch (event) {
    case EV_NONE:
      Serial.print(".");
      break;
    case EV_SHORTPRESS:
      Serial.print("S");
       Serial.print("0");
        digitalWrite(ledPin, LOW);
       digitalWrite(ledPin, HIGH);
       digitalWrite(ledPin, LOW);
      
      break;
    case EV_LONGPRESS:
      Serial.print("L");
      Serial.print("X");
       digitalWrite(ledPin, LOW);
       digitalWrite(ledPin, HIGH);
       digitalWrite(ledPin, LOW);
      break;
  }

  // add newline sometimes
  static int counter = 0;
  if ((++counter & 0x3f) == 0)
    Serial.println();

  delay(DELAY);
}


