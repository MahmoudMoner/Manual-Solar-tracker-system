                                                 //بسم الله الرحمن الرحيم//
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#define IR_RECEIVE_PINs 11 //IR receiver pin
#define SDA A4
#define SCL A5
//Two pin configration//
#define H_BRIDGE_INPUT_ONE 5 //motor2_pin2
#define H_BRIDGE_INPUT_TWO 4 //motor2_pin1
#define H_BRIDGE_INPUT_THREE 3 //motor1_pin2
#define H_BRIDGE_INPUT_FOUR 2 //motor1_pin1
#define BUD_RATE 9600

//Resiver//
IRrecv irrecv(IR_RECEIVE_PINs);
unsigned long key_value=0;
decode_results results;
//lcd
LiquidCrystal_I2C lcd(0x27,20,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

/////////////////setup//////////////////
void setup() {
  
  Serial.begin(BUD_RATE);
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  irrecv.enableIRIn();


/////Motor pins
pinMode(H_BRIDGE_INPUT_ONE,OUTPUT);
pinMode(H_BRIDGE_INPUT_TWO,OUTPUT);
pinMode(H_BRIDGE_INPUT_THREE,OUTPUT);
pinMode(H_BRIDGE_INPUT_FOUR,OUTPUT);


}

//////////////LOOP////////////////
void loop() {
  
 //////////// Manual Control & LCD ////////////////////////////////////////////
if (irrecv.decode()){
    Serial.println (irrecv.decodedIRData.decodedRawData,HEX);
  switch(irrecv.decodedIRData.decodedRawData){
  //MOTOR_A CLOCKWISE MAX SPEED left
  case 0xE0984BB6:
  lcd.clear();
  lcd.print ("L");
  lcd.print ("e");
  lcd.print ("f");
  lcd.print ("t");
  lcd.print ("<");
   digitalWrite(H_BRIDGE_INPUT_TWO, HIGH);
   digitalWrite(H_BRIDGE_INPUT_ONE, LOW);
   delay(50);
   digitalWrite(H_BRIDGE_INPUT_TWO,LOW);
   digitalWrite(H_BRIDGE_INPUT_ONE, LOW);
    break;
  //MOTOR_B CLOCKWISE MAX SPEED down
   case 0x39D41DC6:
  lcd.clear();
  lcd.print ("D");
  lcd.print ("o");
  lcd.print ("w");
  lcd.print ("n");
  lcd.print ("v");
  digitalWrite(H_BRIDGE_INPUT_FOUR, LOW);
  digitalWrite(H_BRIDGE_INPUT_THREE, HIGH);
  delay(50);
  digitalWrite(H_BRIDGE_INPUT_FOUR, LOW);
  digitalWrite(H_BRIDGE_INPUT_THREE, LOW);
  break;
  
  //MOTOR_A COUNTERCLOCKWISE MAX SPEED right
  case 0xA32AB931:
  lcd.clear();
  lcd.print ("R");
  lcd.print ("i");
  lcd.print ("g");
  lcd.print ("h");
  lcd.print ("t");
  digitalWrite(H_BRIDGE_INPUT_TWO, LOW);
  digitalWrite(H_BRIDGE_INPUT_ONE, HIGH);
  delay(50);
  digitalWrite(H_BRIDGE_INPUT_TWO, LOW);
  digitalWrite(H_BRIDGE_INPUT_ONE, LOW);
  break;

  //MOTOR_B COUNTERCLOCKWISE MAX SPEED up
  case 0x371A3C86:
  lcd.clear();
  lcd.print ("U");
  lcd.print ("P");
  lcd.print ("^");
    digitalWrite(H_BRIDGE_INPUT_FOUR, HIGH);
    digitalWrite(H_BRIDGE_INPUT_THREE, LOW);
    delay(50);
    digitalWrite(H_BRIDGE_INPUT_FOUR, LOW);
    digitalWrite(H_BRIDGE_INPUT_THREE, LOW);
     break;

     default:
     lcd.clear();

 }
 irrecv.resume();
   }


 }

   