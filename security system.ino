////////////////////////////////////////////////////////// declerations //////////////////////////////////////////////////////
#include<LiquidCrystal.h>                  // library of lcd
#include<Keypad.h>                     //library of lcd
#include<AccelStepper.h>
unsigned int clian_number_steps = 0;
int  dirz = 51;
int  stepz = 53;
int  diry = 47;
int  stepy = 49;
int limit_switch = 45;
int intial = -1;
char mood = 0;                 // for [correct or not correct password]
unsigned int flag_passwords = 0;
int v = 0;
char cheak[3];                //the array that we used to check if there repeated passwords
unsigned int i = 0;          //counter
char search[3];             //when we search for the the correct password
int b = 0;
int a = 0;                     //used this in  check function
unsigned int j = 0;             // counter
volatile  char key = 0;         //store the password from keypad
volatile  char key1 = 0;       // store the password from keypad in function [give the user]
volatile int change = 0;         //used for the final switch case
int number_of_clients = 0;          //used for number of floor
const char clear_array[3] ;       //that array used to clear the place of the password when the user take his car
volatile char passwords[6][3];           // the main dimensional array that we store the passwords in
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);         ////the definition of the lcd
const byte row = 4;                               // rows of the keypad
const byte col = 4;                                  // colums of the keypad
char keymap[row][col] = {                              // definition the keypad pins
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowpin[row] = {14, 15, 16, 17};                   // rows of the keypad
byte colpin[col] = {18, 19, 20, 21};                         // colums of the keypad
Keypad mykeypad(makeKeymap(keymap), rowpin, colpin, row, col);     //useing the library of keypad
AccelStepper stepperz(1, stepz, dirz);
AccelStepper steppery(1, stepy, diry);
///////////////////////////////////////////////////////////functions definition ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Refernce()
{
  stepperz.setCurrentPosition(0);
  while (digitalRead(limit_switch))
  {
    stepperz.moveTo(intial);
    intial--;
    stepperz.run();
    delay(5);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stepper(int number)
{
  if ( number <= 2 && number >= 1)
  {
    stepperz.setCurrentPosition(0);
    while (stepperz.currentPosition() != 2000)
    {
      stepperz.setSpeed(600);
      stepperz.runSpeed();
    }
    delay(1000);
    steppery.setCurrentPosition(0);
    while (steppery.currentPosition() != 400 * (number - 1))
    {
      steppery.setSpeed(400);
      steppery.runSpeed();
    }
    delay(1000);
/////////////////////////////////////////////////////////////////  revers   ///////////////////////////////////////////////////////
    steppery.setCurrentPosition(0);
    while (steppery.currentPosition() != -400 * (number - 1))
    {
      steppery.setSpeed(-400);
      steppery.runSpeed();
    }
    delay(500);
    stepperz.setCurrentPosition(0);
    while (stepperz.currentPosition() != -1950)
    {
      stepperz.setSpeed(-600);
      stepperz.runSpeed();
    }
  }
///////////////////////////////////////////////////////////////////////////// second floor //////////////////////////////////////
  else if (number >= 3 && number <= 4)
  {
    stepperz.setCurrentPosition(0);
    while (stepperz.currentPosition() != 5200)
    {
      stepperz.setSpeed(600);
      stepperz.runSpeed();
    }
    delay(1000);
    steppery.setCurrentPosition(0);
    while (steppery.currentPosition() != 400 * (number - 3))
    {
      steppery.setSpeed(400);
      steppery.runSpeed();
    }
    delay(1000);
    ///////////////////////////////////////////////////////////  revers   ///////////////////////////////////////////////////////
    steppery.setCurrentPosition(0);
    while (steppery.currentPosition() != -400 * (number - 3))
    {
      steppery.setSpeed(-400);
      steppery.runSpeed();
    }
    delay(500);
    stepperz.setCurrentPosition(0);
    while (stepperz.currentPosition() != -5050)
    {
      stepperz.setSpeed(-600);
      stepperz.runSpeed();
    }
    delay(500);
  }
  ////////////////////////////////////////////////// third floor///////////////////////////////
  else if (number <= 6 && number >= 5)
  {
    stepperz.setCurrentPosition(0);
    while (stepperz.currentPosition() != 8400)
    {
      stepperz.setSpeed(600);
      stepperz.runSpeed();
    }
    delay(1000);
    steppery.setCurrentPosition(0);
    while (steppery.currentPosition() != 400 * (number - 5))
    {
      steppery.setSpeed(400);
      steppery.runSpeed();
    }
    delay(1000);
    ///////////////////////////////////////////////////////////  revers   ///////////////////////////////////////////////////////
    steppery.setCurrentPosition(0);
    while (steppery.currentPosition() != -400 * (number - 5))
    {
      steppery.setSpeed(-400);
      steppery.runSpeed();
    }
    delay(500);
    stepperz.setCurrentPosition(0);
    while (stepperz.currentPosition() != -8350)
    {
      stepperz.setSpeed(-600);
      stepperz.runSpeed();
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////
void Erorr()
{
  delay(500);
  stepperz.setCurrentPosition(0);
  while (stepperz.currentPosition() != 100)
  {
    stepperz.setSpeed(600);
    stepperz.runSpeed();
  }
}
////////////////////////////////////////// take the car from the user ////////////////////////////////////////////////////////////
int take_password_from_user()
{
  if (flag_passwords < 6)               /// there are places in thr gar
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("enter password");
    for (i = 0; i < 3; i++)         ///// take the password from the user and store it in two dimenional array and cheak array
    {
      key = mykeypad.waitForKey();
      delay(50);
      lcd.setCursor(i, 1);
      lcd.print(key);
      passwords[flag_passwords][i] = key;
      cheak[i] = key;
      delay(500);
    }
    lcd.clear();
    flag_passwords++;
  }
  else if (flag_passwords >= 6)   ///// there are no places in the garage so search for the array with zeros values [empty places]
  {
    for ( j = 0; j < 6; j++)
    {
      for (i = 0; i < 3; i++)
        if ( passwords[j][i] == clear_array[i])
        {
          b = j;
          if (b == 2)
          {
            for (i = 0; i < 3; i++)  /////// take the password from the user and store it in two dimenional array and cheak array
            {
              key = mykeypad.waitForKey();
              lcd.setCursor(i, 1);
              lcd.print(key);
              passwords[b][i] = key;
              cheak[i] = key;
              delay(1000);
            }
          }
          else
          {
            b = 0;
            continue;
          }
        }
    }
  }
  return flag_passwords ;
}
/////////////////////////////////////////////////////////////// give the car to the user //////////////////////////////////////////////////
void give_the_user()
{
  lcd.clear();
  lcd.print("enter psaaword");
  lcd.setCursor(0, 1);
  volatile int n = 0;
  for ( i = 0; i < 3; i++)  /////////// let the user enter the password
  {
    key1 = mykeypad.waitForKey();
    lcd.print(key1);
    search[i] = key1;
  }
  for ( i = 0; i < 6; i++) ////////check if the password that entered by the user is correct or not
  {
    for ( j = 0; j < 3; j++)
    {
      if (search[j] == passwords[i][j] )
      {
        n = j;
        if (n == 2)
        {
          v = 2;
          number_of_clients = i;
        }
      }
      else if (search[j] != passwords[i][j])
      {
        n = 0;
        continue;
      }
    }
  }
  if (v == 2)
  {
    change = 1;
  }
  else
  {
    change = 2 ;
  }
  delay(2000);
  switch (change)
  {
    case 1:          ////////// if the password correct print correct and put in his place zeros
      lcd.setCursor(0, 1);
      lcd.print("correct client");
      lcd.setCursor(15, 1);
      lcd.print(number_of_clients);
      delay(1000);
      for (i = 0; i < 3; i++)
      {
        passwords[number_of_clients][i] = clear_array[i];
      }
      v = 0;
      break;
    case 2:   /////////// if the password not correct print incorrect
      lcd.setCursor(0, 1);
      lcd.print("incorrect pass");
      n = 0;
      break;
    default :
      lcd.setCursor(0, 1);
      lcd.print("dincorrect pass");
  }
  delay(1000);
  lcd.clear();
  lcd.print("thanks");
  delay(1000);
  return  (number_of_clients + 1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  lcd.begin(2, 16);
  lcd.cursor();
  lcd.clear();
  stepperz.setMaxSpeed(600);
  steppery.setMaxSpeed(100);
  pinMode(dirz, OUTPUT);
  pinMode(stepz, OUTPUT);
  pinMode(diry, OUTPUT);
  pinMode(stepy, OUTPUT);
  pinMode(limit_switch, INPUT_PULLUP);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Welcome sir");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("(1)in or (2)out");
  mood = mykeypad.waitForKey();
  lcd.setCursor(0, 1);
  lcd.print(mood);
  delay(1000);
  switch (mood)
  {
//////////////////////////////// if you press one you will enter the password and the car will be taken to place .
/////////////////////////////// if you press two you will enter the password that you saved and the car will be taken dawn .
    case '1':
      lcd.clear();
      clian_number_steps = take_password_from_user();
      lcd.setCursor(0, 0);
      lcd.print("thanks,");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SaveYourPass");
      delay(1000);
      lcd.clear();
      delay(3000);
      Refernce();
      delay(750);
      stepper(clian_number_steps);
      delay(2000);
      Refernce();
      delay(750);
      Erorr();
      delay(1000);
      break;
    case '2':    /////////////////////////////// if you press two you will enter the password that you saved and the car will be taken dawn .
      clian_number_steps =  give_the_user();
      Refernce();
      delay(750);
      stepper( clian_number_steps);
      delay(2000);
      Erorr();
      delay(1000);
      break;
  }
  delay(2000);
}
