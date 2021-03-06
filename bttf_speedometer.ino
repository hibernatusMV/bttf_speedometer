#define LATCH 4
#define CLK 3
#define DATA 2

byte digit[10]= {0x6F, 0x09, 0x73, 0x3B, 0x1D, 0x3E, 0x7C, 0x0B, 0x7F, 0x1F};

int i;
int j;

void setup(){
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);

  initDisplay();
}

void loop(){
  for (i=1; i<=88; i++) {
    // Accelerate
    if (i<=25) delay(100);
    if ((i>25) && (i<=80)) delay(200);
    if ((i>80) && (i<=88)) delay(400);

    int firstDigit = i/10;
    int secondDigit = i%10;

    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLK, MSBFIRST, ~digit[secondDigit]); // digitOne
    
    if (firstDigit > 0) {
      shiftOut(DATA, CLK, MSBFIRST, ~digit[firstDigit]); // digitTwo 
    } else {
      shiftOut(DATA, CLK, MSBFIRST, B11111111); // digitOne
    }
    digitalWrite(LATCH, HIGH);
  }
  
  if(i > 88) {
    delay(5000);
    // Brake
    for (j=88; j>=1; j--) {
      delay(50);
      int firstDigit = j/10;
      int secondDigit = j%10;
  
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLK, MSBFIRST, ~digit[secondDigit]); // digitOne
      
      if (firstDigit > 0) {
        shiftOut(DATA, CLK, MSBFIRST, ~digit[firstDigit]); // digitTwo 
      } else {
        shiftOut(DATA, CLK, MSBFIRST, B11111111); // digitOne
      }
      digitalWrite(LATCH, HIGH);
    }
    initDisplay();
  }
}

void initDisplay(){
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLK, MSBFIRST, ~digit[0]); // digitOne
  shiftOut(DATA, CLK, MSBFIRST, B11111111); // digitOne
  digitalWrite(LATCH, HIGH);
  delay(2500);
}
