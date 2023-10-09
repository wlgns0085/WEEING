#include <hidboot.h>
#include <usbhub.h>

#include <Keyboard.h>
#include "special_keys.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

bool macro_curr = false, macro_prev = false;



class KbdRptParser : public KeyboardReportParser
{
    void PrintKey(uint8_t mod, uint8_t key);

  protected:
    void OnControlKeysChanged(uint8_t before, uint8_t after);

    void OnKeyDown  (uint8_t mod, uint8_t key);
    void OnKeyUp  (uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);
};

void KbdRptParser::PrintKey(uint8_t m, uint8_t key)
{
  MODIFIERKEYS mod;
  *((uint8_t*)&mod) = m;
  Serial.print((mod.bmLeftCtrl   == 1) ? "C" : " ");
  Serial.print((mod.bmLeftShift  == 1) ? "S" : " ");
  Serial.print((mod.bmLeftAlt    == 1) ? "A" : " ");
  Serial.print((mod.bmLeftGUI    == 1) ? "G" : " ");

  Serial.print(key);
  Serial.print(" (0x");
  PrintHex<uint8_t>(key, 0x80);
  Serial.print(")");

  Serial.print((mod.bmRightCtrl   == 1) ? "C" : " ");
  Serial.print((mod.bmRightShift  == 1) ? "S" : " ");
  Serial.print((mod.bmRightAlt    == 1) ? "A" : " ");
  Serial.println((mod.bmRightGUI    == 1) ? "G" : " ");
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
  Serial.print("PUSH    ");
  PrintKey(mod, key);
  uint8_t c = OemToAscii(mod, key);
  
  switch(key){
    case READ_TAB:
        Keyboard.press(KEY_TAB); Serial.println("[tab]");
      break;
    case READ_CAPS_LOCK:
        Keyboard.press(KEY_CAPS_LOCK); Serial.println("[capslock]");
      break;
    case READ_BACKSPACE:
        Keyboard.press(KEY_BACKSPACE); Serial.println("[backspace]");
      break;
    case READ_RETURN:
        Keyboard.press(KEY_RETURN); Serial.println("[return]");
      break;
//    case READ_MENU:
//        Keyboard.press(KEY_MENU); Serial.println("[menu]");
//      break;

    case READ_INSERT:
        Keyboard.press(KEY_INSERT); Serial.println("[insert]");
      break;
    case READ_DELETE:
        Keyboard.press(KEY_DELETE); Serial.println("[delete]");
      break;
    case READ_HOME:
        Keyboard.press(KEY_HOME); Serial.println("[home]");
      break;
    case READ_END:
        Keyboard.press(KEY_END); Serial.println("[end]");
      break;
    case READ_PAGE_UP:
        Keyboard.press(KEY_PAGE_UP); Serial.println("[page up]");
      break;
    case READ_PAGE_DOWN:
        Keyboard.press(KEY_PAGE_DOWN); Serial.println("[page down]");
      break;
      
    case READ_UP_ARROW:
        Keyboard.press(KEY_UP_ARROW); Serial.println("[up]");
      break;
    case READ_DOWN_ARROW:
        Keyboard.press(KEY_DOWN_ARROW); Serial.println("[down]");
      break;
    case READ_LEFT_ARROW:
        Keyboard.press(KEY_LEFT_ARROW); Serial.println("[left]");
      break;
    case READ_RIGHT_ARROW:
        Keyboard.press(KEY_RIGHT_ARROW); Serial.println("[right]");
      break;

    case READ_PRINT_SCREEN:
        Keyboard.press(KEY_PRINT_SCREEN); Serial.println("[print screen]");
      break;
      
    default:
        Serial.print("[");
        Serial.print((char)c);
        Serial.println("]");
        Keyboard.press(c);
      break;
  }
  
//  if (c){
//    OnKeyPressed(c);
//  }

}

void KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after) {

  MODIFIERKEYS beforeMod;
  *((uint8_t*)&beforeMod) = before;

  MODIFIERKEYS afterMod;
  *((uint8_t*)&afterMod) = after;
  
  if(after == 7){
    Serial.println("Macro State changed");
    macro_curr = !macro_curr;
  }

  if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl) {
    if(after & 1) {Keyboard.press(KEY_LEFT_CTRL); Serial.println("LeftCtrl pushed");}
    else {Keyboard.release(KEY_LEFT_CTRL); Serial.println("LeftCtrl released");}
  }
  if (beforeMod.bmLeftShift != afterMod.bmLeftShift) {
    if(after & 1<<1) {Keyboard.press(KEY_LEFT_SHIFT); Serial.println("LeftShift pushed");}
    else {Keyboard.release(KEY_LEFT_SHIFT); Serial.println("LeftShift released");}
  }
  if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt) {
    if(after & 1<<2) {Keyboard.press(KEY_LEFT_ALT); Serial.println("LeftAlt pushed");}
    else {Keyboard.release(KEY_LEFT_ALT); Serial.println("LeftAlt released");}
  }
  if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI) {
    if(after & 1<<3) {Keyboard.press(KEY_LEFT_GUI); Serial.println("LeftGUI pushed");}
    else {Keyboard.release(KEY_LEFT_GUI); Serial.println("LeftGUI released");}
  }

  if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl) {
    if(after & 1<<4) {Keyboard.press(KEY_RIGHT_CTRL); Serial.println("RightCtrl pushed");}
    else {Keyboard.release(KEY_RIGHT_CTRL); Serial.println("RightCtrl released");}
  }
  if (beforeMod.bmRightShift != afterMod.bmRightShift) {
    if(after & 1<<5) {Keyboard.press(KEY_RIGHT_SHIFT); Serial.println("RightShift pushed");}
    else {Keyboard.release(KEY_RIGHT_SHIFT); Serial.println("RightShift released");}
  }
  if (beforeMod.bmRightAlt != afterMod.bmRightAlt) {
    if(after & 1<<6) {Keyboard.press(KEY_RIGHT_ALT); Serial.println("RightAlt pushed");}
    else {Keyboard.release(KEY_RIGHT_ALT); Serial.println("RightAlt released");}
  }
  if (beforeMod.bmRightGUI != afterMod.bmRightGUI) {
    if(after & 1<<7) {Keyboard.press(KEY_RIGHT_GUI); Serial.println("RightGUI pushed");}
    else {Keyboard.release(KEY_RIGHT_GUI); Serial.println("RightGUI released");}
  }

}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
  Serial.print("RELEASE ");
  PrintKey(mod, key);
  uint8_t c = OemToAscii(mod, key);

  switch(key){
        case READ_TAB:
        Keyboard.release(KEY_TAB); Serial.println("[tab]");
      break;
    case READ_CAPS_LOCK:
        Keyboard.release(KEY_CAPS_LOCK); Serial.println("[capslock]");
      break;
    case READ_BACKSPACE:
        Keyboard.release(KEY_BACKSPACE); Serial.println("[backspace]");
      break;
    case READ_RETURN:
        Keyboard.release(KEY_RETURN); Serial.println("[return]");
      break;
//    case READ_MENU:
//        Keyboard.release(KEY_MENU); Serial.println("[menu]");
//      break;
      
    case READ_INSERT:
        Keyboard.release(KEY_INSERT); Serial.println("[insert]");
      break;
    case READ_DELETE:
        Keyboard.release(KEY_DELETE); Serial.println("[delete]");
      break;
    case READ_HOME:
        Keyboard.release(KEY_HOME); Serial.println("[home]");
      break;
    case READ_END:
        Keyboard.release(KEY_END); Serial.println("[end]");
      break;
    case READ_PAGE_UP:
        Keyboard.release(KEY_PAGE_UP); Serial.println("[page up]");
      break;
    case READ_PAGE_DOWN:
        Keyboard.release(KEY_PAGE_DOWN); Serial.println("[page down]");
      break;
      
    case READ_UP_ARROW:
        Keyboard.release(KEY_UP_ARROW); Serial.println("[up]");
      break;
    case READ_DOWN_ARROW:
        Keyboard.release(KEY_DOWN_ARROW); Serial.println("[down]");
      break;
    case READ_LEFT_ARROW:
        Keyboard.release(KEY_LEFT_ARROW); Serial.println("[left]");
      break;
    case READ_RIGHT_ARROW:
        Keyboard.release(KEY_RIGHT_ARROW); Serial.println("[right]");
      break;

    case READ_PRINT_SCREEN:
        Keyboard.release(KEY_PRINT_SCREEN); Serial.println("[print screen]");
      break;
            
    default:
        Serial.print("[");
        Serial.print((char)c);
        Serial.println("]");
        Keyboard.release(c);
      break;
  }
}

void KbdRptParser::OnKeyPressed(uint8_t key)
{
  Serial.print("ASCII: ");
  Serial.println((char)key);
};

USB     Usb;
//USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

KbdRptParser Prs;
