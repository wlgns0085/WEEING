#include "USB_HostShield.h"

void setup()
{
  
  
  Keyboard.begin();
  
  Serial.begin( 115200 );
  
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif

  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  while (Usb.Init() == -1){
    Serial.println("wait for OSC to start ...");
    delay( 500 );
  }

  delay( 200 );

  HidKeyboard.SetReportParser(0, &Prs);
}




void loop()
{
  if(macro_curr != macro_prev){
    Serial.println(macro_curr);
    macro_prev = macro_curr;
  }
  
  Usb.Task();
  
}
