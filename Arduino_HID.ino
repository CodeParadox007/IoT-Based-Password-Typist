#include<Dictionary.h>
#include<SoftwareSerial.h>
SoftwareSerial SUART(10, 11);
#define KEY_LEFT_CTRL 1
#define KEY_LEFT_SHIFT 2
// #include <exception>
// class MyException : public std::exception {
//   // define your custom exception class
// };

//Dictionary<String, String> MyDict = Dictionary<String, String>();

uint8_t buf[8] = {
  0
};

bool currState_W = LOW;
bool prevState_W = LOW; 

bool currState_v = LOW;
bool prevState_v = LOW; 

unsigned long prevTime_W = 0;
unsigned long waitTime_W = 50;

unsigned long prevTime_v = 0;
unsigned long waitTime_v = 50;

Dictionary<char, int> MyDict;

char ch;
String S;
int i=0;
int len=0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SUART.begin(9600);
  pinMode(8,INPUT);
  pinMode(9,INPUT);


  

}

void loop() {
  // put your main code here, to run repeatedly:
 
//Serial.println(dic(S[0]));

//for(int i=0;i<sizeof(S)-1;i++){
//  Serial.print(dic(S[i]));
//  Serial.print(" ");
//}
//Serial.println(" ");

while (SUART.available() != 0 )
  {
    ch= SUART.read();
S+=ch;
//   try
//     {

// len=int(ch);      
//     }
//   catch (ExceptionType e)
//     {
    
//     }


//Serial.print(char(ch));

  }
  checkButton();
//  Serial.println(S);

//  Serial.println(S.length());
  // S="";

  
//  delay(1000);


  
//  delay(1000);
//delay(1000);

  

//for(int i=0;i<sizeof(S);i++){
//  Serial.print(S[i]);
//}
//Serial.println(" ");






}

void checkButton(){
   bool currRead_W = digitalRead(8);
  bool currRead_v = digitalRead(9);

  if (currRead_v != prevState_v) {
    prevTime_v = millis();
  }

    if ((millis() - prevTime_v) > waitTime_v) {
    if (currRead_v != currState_v) {
      currState_v = currRead_v;
      if (currState_v ==HIGH) {
// Serial.println("In Space");
         {
                buf[2] = 44;           // HID: W key
        Serial.write(buf, 8); // Send keypress
        releaseKey();
        }
        delay(1000);
           
        
        
      }
    }
  }
delay(200);

if ((millis() - prevTime_W) > waitTime_W) {
  if (currRead_W != currState_W) {
    currState_W = currRead_W;
    if (currState_W == HIGH) {
      // Serial.println("In Pass");
      for (int i = 0; i < 13; i++) {
        if (isUpperCase(S[i])) {
          key_press_upper(dic(S[i]));
        }
        if (isLowerCase(S[i])) {
          key_press(dic(S[i]));
        }
        if (isDigit(S[i])) {
          key_press(dic(S[i]));
        }
        if (S[i] == '!' || S[i] == '@' || S[i] == '#' || S[i] == '$' || S[i] == '%' || S[i] == '^' || S[i] == '&' || S[i] == '*' || S[i] == '(' || S[i] == ')'|| S[i] == ' ') {
          key_press(dic(S[i]));
        }
        //  Serial.print(" ");
        //  Serial.println(dic(S[i]));        
        //  Serial.print(" Pressed");
        
      }
                {
        buf[2] = 40;           // HID: Space key
        Serial.write(buf, 8); // Send keypress
        releaseKey();
        }
        S="";
  
  }        
}
  }

  



  prevState_W = currRead_W;
  prevState_v = currRead_v;

  

}


int dic(char s){
  MyDict.set('a',4);
  MyDict.set('b',5);
  MyDict.set('c',6);
  MyDict.set('d',7);
  MyDict.set('e',8);
  MyDict.set('f',9);
  MyDict.set('g',10);
  MyDict.set('h',11);
  MyDict.set('i',12);
  MyDict.set('j',13);
  MyDict.set('k',14);
  MyDict.set('l',15);
  MyDict.set('m',16);
  MyDict.set('n',17);
  MyDict.set('o',18);
  MyDict.set('p',19);
  MyDict.set('q',20);
  MyDict.set('r',21);
  MyDict.set('s',22);
  MyDict.set('t',23);
  MyDict.set('u',24);
  MyDict.set('v',25);
  MyDict.set('w',26);
  MyDict.set('x',27);
  MyDict.set('y',28);
  MyDict.set('z',29);
  
  MyDict.set('0',39);
  MyDict.set('1',30);
  MyDict.set('2',31);
  MyDict.set('3',32);
  MyDict.set('4',33);
  MyDict.set('5',34);
  MyDict.set('6',35);
  MyDict.set('7',36);
  MyDict.set('8',37);
  MyDict.set('9',38);
  MyDict.set('C',41); //ESC
  MyDict.set('B',42); //Backspace
  MyDict.set('E',40); //Enter

  MyDict.set('\\',49); 
  MyDict.set('[',47);
  MyDict.set(']',48);
  MyDict.set(',',54);
  MyDict.set('.',55);
  MyDict.set('/',56);
  MyDict.set('`',53);
  MyDict.set('T',43); //Tab
  MyDict.set('*',85);


  //upper
MyDict.set('A',4);
  MyDict.set('B',5);
  MyDict.set('C',6);
  MyDict.set('D',7);
  MyDict.set('E',8);
  MyDict.set('F',9);
  MyDict.set('G',10);
  MyDict.set('H',11);
  MyDict.set('I',12);
  MyDict.set('J',13);
  MyDict.set('K',14);
  MyDict.set('L',15);
  MyDict.set('M',16);
  MyDict.set('N',17);
  MyDict.set('O',18);
  MyDict.set('P',19);
  MyDict.set('Q',20);
  MyDict.set('R',21);
  MyDict.set('S',22);
  MyDict.set('T',23);
  MyDict.set('U',24);
  MyDict.set('V',25);
  MyDict.set('W',26);
  MyDict.set('X',27);
  MyDict.set('Y',28);
  MyDict.set('Z',29);  

  //Special
  MyDict.set('!',207);
  MyDict.set('@',206);
  MyDict.set('#',204);
  MyDict.set('|',201); //
  MyDict.set('%',196);
  MyDict.set('^',195);
  MyDict.set('&',199);
  MyDict.set('*',85);
  MyDict.set('(',182);
  MyDict.set(')',183);
  MyDict.set('+',87);
  MyDict.set(' ',44); //Space
  MyDict.set('\\',49); 
  MyDict.set('[',47);
  MyDict.set(']',48);
  MyDict.set(',',54);
  MyDict.set('.',55);
  MyDict.set('/',56);
  MyDict.set('`',53);
  MyDict.set('T',43); //Tab

  
  // MyDict.set('k',14);
  // MyDict.set('l',15);
  // MyDict.set('m',16);
  // MyDict.set('n',17);
  // MyDict.set('o',18);
  // MyDict.set('p',19);
  // MyDict.set('q',20);
  // MyDict.set('r',21);
  // MyDict.set('s',22);
  // MyDict.set('t',23);
  // MyDict.set('u',24);
  // MyDict.set('v',25);
  // MyDict.set('w',26);
  // MyDict.set('x',27);
  // MyDict.set('y',28);
  // MyDict.set('z',29);  
  


  return MyDict.get(s);
}
void key_press(int x){
  
        buf[2] = x;           // HID: W key
        Serial.write(buf, 8); // Send keypress
        releaseKey();
}
void key_press_upper(int x){
{
    buf[0] =KEY_LEFT_SHIFT;   // Ctrl
    buf[2] = x;    // Letter A

    Serial.write(buf, 8); // Send keypress
    releaseKey();
}  
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key  
  delay(100);
}
