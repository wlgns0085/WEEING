
#define KEY_F1     '1'
#define KEY_F2     '2'
#define KEY_SHIFT  '3'
#define KEY_LEFT   '4'
#define KEY_RIGHT  '5'
#define KEY_DOWN   '6'
#define KEY_UP     '7'

enum {
  INDEX_LEFT = 0,
  INDEX_RIGHT,
  INDEX_DOWN,
  INDEX_UP,
  INDEX_SHIFT,
  INDEX_F1,
  INDEX_F2,
  INDEX_C,
  INDEX_X,
  INDEX_D,
  INDEX_E,
  INDEX_R,
  INDEX_G,
  INDEX_N,
  INDEX_M,
  INDEX_J,
  NUM_INDEX
};



int incomingByte = -1;
unsigned long currentMillis;
unsigned long endOfPress[NUM_INDEX];
uint8_t pin[NUM_INDEX] = {
  2, 3, 4, 5,
  11, A3, A2, 7,
  10, A4, 9, 8,
  A5, 12, 6, A6
};

void setup() {
  Serial1.begin(115200);

  // Digital Pin 2 ~ 12 (11)
  for(int i=2; i<=12; i++) {
    pinMode(i, OUTPUT);
  }
  
  // Analog Pin 2 ~ 6 (5)
  for(uint8_t i=A2; i<=A6; i++) {
    pinMode(i, OUTPUT);
  }
  
  // pinMode(LED_BUILTIN, OUTPUT); // 내장 LED 핀 설정
}

void loop() {
  currentMillis = millis();
  for(int i=0; i<NUM_INDEX; i++)
  {
    if(currentMillis >= endOfPress[i] && endOfPress[i] != 0)
    {
      digitalWrite(pin[i], LOW);
      endOfPress[i] = 0;
    }
  }


  if(Serial1.available() > 0)
  {
    incomingByte = Serial1.read();
    Serial1.print("(0x");
    Serial1.print(incomingByte, DEC);
    Serial1.print(") ");
  }

  switch(incomingByte)
  {
    case KEY_F1:
      Serial1.println("F1 function");
      endOfPress[INDEX_F1] = currentMillis + 50;
      digitalWrite(pin[INDEX_F1], HIGH);
      break;
    case KEY_F2:
      Serial1.println("F2 function");
      endOfPress[INDEX_F2] = currentMillis + 50;
      digitalWrite(pin[INDEX_F2], HIGH);
      break;
    case KEY_SHIFT:
      Serial1.println("Shift function");
      endOfPress[INDEX_SHIFT] = currentMillis + 50;
      digitalWrite(pin[INDEX_SHIFT], HIGH);
      break;
    case KEY_LEFT:
      Serial1.println("Left function");
      endOfPress[INDEX_LEFT] = currentMillis + 50;
      digitalWrite(pin[INDEX_LEFT], HIGH);
      break;
    case KEY_RIGHT:
      Serial1.println("Right function");
      endOfPress[INDEX_RIGHT] = currentMillis + 50;
      digitalWrite(pin[INDEX_RIGHT], HIGH);
      break;
    case KEY_DOWN:
      Serial1.println("Down function");
      endOfPress[INDEX_DOWN] = currentMillis + 50;
      digitalWrite(pin[INDEX_DOWN], HIGH);
      break;
    case KEY_UP:
      Serial1.println("Up function");
      endOfPress[INDEX_UP] = currentMillis + 50;
      digitalWrite(pin[INDEX_UP], HIGH);
      break;

    case 'c':
      Serial1.println("C function");
      endOfPress[INDEX_C] = currentMillis + 50;
      digitalWrite(pin[INDEX_C], HIGH);
      break;
    case 'x':
      Serial1.println("X function");
      endOfPress[INDEX_X] = currentMillis + 50;
      digitalWrite(pin[INDEX_X], HIGH);
      break;
    case 'd':
      Serial1.println("D function");
      endOfPress[INDEX_D] = currentMillis + 50;
      digitalWrite(pin[INDEX_D], HIGH);
      break;

    case 'e':
      Serial1.println("E function");
      endOfPress[INDEX_E] = currentMillis + 50;
      digitalWrite(pin[INDEX_E], HIGH);
      break;
    case 'r':
      Serial1.println("R function");
      endOfPress[INDEX_R] = currentMillis + 50;
      digitalWrite(pin[INDEX_R], HIGH);
      break;
    case 'g':
      Serial1.println("G function");
      endOfPress[INDEX_G] = currentMillis + 50;
      digitalWrite(pin[INDEX_G], HIGH);
      break;

    case 'n':
      Serial1.println("N function");
      endOfPress[INDEX_N] = currentMillis + 50;
      digitalWrite(pin[INDEX_N], HIGH);
      break;
    case 'm':
      Serial1.println("M function");
      endOfPress[INDEX_M] = currentMillis + 50;
      digitalWrite(pin[INDEX_M], HIGH);
      break;
    case 'j':
      Serial1.println("J function");
      endOfPress[INDEX_J] = currentMillis + 50;
      digitalWrite(pin[INDEX_J], HIGH);
      break;

    case -1:
      break;

    default:
      Serial1.println();
      ;
  }
  incomingByte = -1;
}
