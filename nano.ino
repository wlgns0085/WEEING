#define UART_F1     '1'
#define UART_F2     '2'
#define UART_SHIFT  '3'
#define UART_LEFT   '5'
#define UART_RIGHT  '6'
#define UART_DOWN   '7'
#define UART_UP     '8'

int incomingByte = -1;
unsigned long currentMillis;

void setup() {
  Serial1.begin(115200);

  // Digital Pin 2 ~ 12 (11)
  for(int i=2; i<=12; i++)
    pinMode(i, OUTPUT);
  
  // Analog Pin 2 ~ 6 (5)
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);

  // pinMode(LED_BUILTIN, OUTPUT); // 내장 LED 핀 설정
}

void loop() {
  currentMillis = millis();

  if(Serial1.available() > 0)
  {
    incomingByte = Serial1.read();
    Serial1.print("echo: ");
    Serial1.println(incomingByte, DEC);
  }

  switch(incomingByte)
  {
    case '1':
      Serial1.println("F1 function");
      Serial1.println(currentMillis);
      break;
    case '2':
      Serial1.println("F2 function");
      break;
    case '3':
      Serial1.println("Shift function");
      break;
    case '5':
      Serial1.println("Left function");
      break;
    case '6':
      Serial1.println("Right function");
      break;
    case '7':
      Serial1.println("Down function");
      break;
    case '8':
      Serial1.println("Up function");
      break;

    case 'c':
      Serial1.println("C function");
      // digitalWrite(7, HIGH); 
      // delay(70);
      // digitalWrite(7, LOW);
      // delay(500);
      break;
    case 'x':
      Serial1.println("C function");
      break;
    case 'd':
      Serial1.println("D function");
      break;

    case 'e':
      Serial1.println("E function");
      break;
    case 'r':
      Serial1.println("R function");
      break;
    case 'g':
      Serial1.println("G function");
      break;

    case 'n':
      Serial1.println("N function");
      break;
    case 'm':
      Serial1.println("M function");
      break;
    case 'j':
      Serial1.println("J function");
      break;

    default:
      ;
  }
  incomingByte = -1;

  //     String received = Serial1.readStringUntil('\n'); // 문자열 읽기
  //     Serial1.print("Echo: ");
  //     Serial1.println(received); // 받은 문자열 Echo

  //     byte = received.toInt(); 
  //     Serial1.println(byte);
  //     if(byte >= 2 && byte <= 12)
  //     {
  //       digitalWrite(byte, HIGH); 
  //       delay(500);
  //       digitalWrite(byte, LOW);  // 디지털 핀 13 끄기
  //     }
  //     else if(byte == 13)
  //     {
  //       digitalWrite(A6, HIGH); 
  //       delay(500);
  //       digitalWrite(A6, LOW);
  //     }
  //     else if(byte == 14)
  //     {
  //       digitalWrite(A5, HIGH); 
  //       delay(500);
  //       digitalWrite(A5, LOW);
  //     }
  //     else if(byte == 15)
  //     {
  //       digitalWrite(A4, HIGH); 
  //       delay(500);
  //       digitalWrite(A4, LOW);
  //     }
  //     else if(byte == 16)
  //     {
  //       digitalWrite(A3, HIGH); 
  //       delay(500);
  //       digitalWrite(A3, LOW);
  //     }
  //     else if(byte == 17)
  //     {
  //       digitalWrite(A2, HIGH); 
  //       delay(500);
  //       digitalWrite(A2, LOW);
  //     }
  //     else if(byte == 21)
  //     {
  //       digitalWrite(2, HIGH);
  //       digitalWrite(5, HIGH);
  //       delay(500);
  //       digitalWrite(2, LOW);
  //       digitalWrite(5, LOW);
  //     }
  //     else if(byte == 22)
  //     {
  //       digitalWrite(3, HIGH);
  //       digitalWrite(5, HIGH);
  //       delay(500);
  //       digitalWrite(3, LOW);
  //       digitalWrite(5, LOW);
  //     }
  //     else if(byte == 23)
  //     {
  //       digitalWrite(3, HIGH);
  //       digitalWrite(4, HIGH);
  //       delay(500);
  //       digitalWrite(3, LOW);
  //       digitalWrite(4, LOW);
  //     }
  //     else if(byte == 24)
  //     {
  //       digitalWrite(2, HIGH);
  //       digitalWrite(4, HIGH);
  //       delay(500);
  //       digitalWrite(2, LOW);
  //       digitalWrite(4, LOW);
  //     }
      
  //   }
    

}
