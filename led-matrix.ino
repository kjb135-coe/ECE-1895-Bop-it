#include <LedControl.h>

#include <LedControl.h>

#include <LedControl.h>

#include "LedControl.h"

//CLK is 13
//CS is 12
//DIN is 11

LedControl lc=LedControl(11,13,12,4);  // Pins: DIN,CLK,CS, # of Display connected

unsigned long delayTime=200;  // Delay between Frames


//lc.setRow(1, 0, B11100000);




void clear(){
  for(int i=0; i<4; i++)
    lc.clearDisplay(i);
}


void display(byte word[], int start, int size){
  for(int i=start; i<size; i++){
    if(i<0)
      lc.setColumn(3-i/8, i%8, word[i+start]);
  }
}


////////LOADING UP SCREEN//////////
byte leftPunch[] = 
{
  B01111100,
  B01000100,
  B01111110,
  B01111010,
  B01111110,
  B01111000,
  B01111000,
  B00111000
};



//Punches left glove across the screen
//i is the tip of the glove
//j is the bytes of the punching glove
void loadingScreen(){
  clear();
  for(int i=0; i<32; i++){
    for(int j=0; j<8; j++){
      if(j <= i)
        lc.setColumn(3-(i-j)/8, (i-j)%8, leftPunch[j]);  
    }
    delay(50);
  }
  
  delay(1000);
  clear();
}


/////////START SCREEN/////////

byte start[] =
{
  B01110010,
  B01010010,
  B01011110,
  B00100000,
  B01111110,
  B00100000,
  B00000000,
  B00011110,

  B00010100,
  B00011110,
  B00000000,
  B00011110,
  B00010000,
  B00100000,
  B01111110,
  B00100000
};


//This puts the word start at the center of the screen
void showStart() {
  for (int i = 0; i < 16; i++)
  {
    lc.setColumn(2-i/8, i%8, start[i]);
  }
}


//Extended punch on both sides
void punchIn()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setColumn(3, 7-i, leftPunch[i]);
    lc.setColumn(0, i, leftPunch[i]);
  }

  delay(2000);
}

//Retracted punch on both sides
void punchOut()
{
  lc.setColumn(3, 7, B00000000);
  lc.setColumn(0, 0, B00000000);
  for (int i = 0; i < 7; i++)
  {
    lc.setColumn(3, 6-i, leftPunch[i]);
    lc.setColumn(0, 1+i, leftPunch[i]);
  }
  delay(2000);
}


void startScreen()
{
  clear();
  showStart();
  for(int i=0; i<20; i++){
    punchIn();
    punchOut();
  }
}


////////DODGE/////////

byte dodge[] = 
{
  //D, half of O
  B01111110,
  B01000010,
  B01000010,
  B00100100,
  B00011000,
  B00000000,
  B01111110,
  B01000010,

  //half of O, D
  B01000010,
  B01111110,
  B00000000,
  B01111110,
  B01000010,
  B01000010,
  B00100100,
  B00011000,

  //G, most of E
  B00000000,
  B01111110,
  B01000010,
  B01001010,
  B01001110,
  B00000000,
  B01111110,
  B01010010,

  //byte of E, slipstream
  B01010010,



  B00000000,
  B00010010,
  B00100100,
  B01001000,
  B01001000,
  B00100100,
  B00010010,

  //slipstream
  B00010010,
  B00100100,
  B01001000,
  B01001000,
  B00100100,
  B00010010,
  B00010010,
  B00100100,

  //slipstream
  B01001000,
  B01001000,
  B00100100,
  B00010010,
  B00010010,
  B00100100,
  B01001000,
  B01001000,
  B00100100,
  B00010010,

  //slipstream
  B00010010,
  B00100100,
  B01001000,
  B01001000,
  B00100100,
  B00010010,
  B00010010,
  B00100100
};



void showDodge(){
  //Will display 4 from the left and 5 from the right
  
  //**
  lc.setColumn(3, 0, B00000000);
  lc.setColumn(3, 1, B01000100);
  lc.setColumn(3, 2, B10101010);
  //**
  
  for(int i=4; i<30; i++){
    lc.setColumn(3-i/8, i%8, dodge[i-4]);
  }

  //**
  lc.setColumn(0, 5, B00000000);
  lc.setColumn(0, 6, B01000100);
  lc.setColumn(0, 7, B10101010);
  //**
}

void dodgeArrows(){
  for(int i=1; i<8; i++){
    if(i%2){  //Extended
      lc.setColumn(3, 0, B01000010);
      lc.setColumn(3, 1, B10100101);
      lc.setColumn(3, 2, B00000000);
      lc.setColumn(0, 5, B01000010);
      lc.setColumn(0, 6, B10100101);
      lc.setColumn(0, 7, B00000000);
      delay(600);
    }
    else{   //Retracted
      lc.setColumn(3, 0, B00000000);
      lc.setColumn(3, 1, B01000010);
      lc.setColumn(3, 2, B10100101);
      lc.setColumn(0, 5, B00000000);
      lc.setColumn(0, 6, B01000010);
      lc.setColumn(0, 7, B10100101);
      delay(300);
    }
  }
}

void dodgeScreen(){
  clear();
  showDodge();
  dodgeArrows();
}


/////////PUNCH////////

byte punch[] = 
{
  //P and U
  B01111110,
  B01010000,
  B01110000,
  B00000000,
  B01111110,
  B00000010,
  B01111110,
  B00000000,

  //N and C
  B01111110,
  B00100000,
  B00010000,
  B01111110,
  B00000000,
  B01111110,
  B01000010,
  B01000010,

  //H
  B00000000,
  B01111110,
  B00010000,
  B01111110
};

void showPunch(){
  for(int i=6; i<26; i++){
    lc.setColumn(3-i/8, i%8, punch[i-6]);
  }
}

void explosion(){
  for(int i=0; i<7; i++){
    if(i%7 == 0){  //Extended
      lc.setColumn(3, 0, B00000000);
      lc.setColumn(3, 1, B00000000);
      lc.setColumn(3, 2, B00000000);
      lc.setColumn(3, 3, B00000000);
      lc.setColumn(3, 4, B00011000);
      lc.setColumn(0, 3, B00011000);
      lc.setColumn(0, 4, B00000000);
      lc.setColumn(0, 5, B00000000);
      lc.setColumn(0, 6, B00000000);
      lc.setColumn(0, 7, B00000000);
      delay(80);
    }
    else if(i%7 == 1){   //Retracted
      lc.setColumn(3, 3, B00011000);
      lc.setColumn(3, 4, B00100100);
      lc.setColumn(0, 4, B00011000);
      lc.setColumn(0, 3, B00100100);
      delay(80);
    }
    else if(i%7 == 2){   //Retracted
      lc.setColumn(3, 2, B00011000);
      lc.setColumn(3, 3, B00100100);
      lc.setColumn(3, 4, B01000010);
      lc.setColumn(0, 5, B00011000);
      lc.setColumn(0, 4, B00100100);
      lc.setColumn(0, 3, B01000010);
      delay(80);
    }
    else if(i%7 == 3){   //Retracted
      lc.setColumn(3, 1, B00011000);
      lc.setColumn(3, 2, B00100100);
      lc.setColumn(3, 3, B01000010);
      lc.setColumn(3, 4, B10000001);
      lc.setColumn(0, 6, B00011000);
      lc.setColumn(0, 5, B00100100);
      lc.setColumn(0, 4, B01000010);
      lc.setColumn(0, 3, B10000001);
      delay(80);
    }
    else if(i%7 == 4){   //Retracted
      lc.setColumn(3, 0, B00011000);
      lc.setColumn(3, 1, B00100100);
      lc.setColumn(3, 2, B01000010);
      lc.setColumn(3, 3, B10000001);
      lc.setColumn(3, 4, B00000000);
      lc.setColumn(0, 7, B00011000);
      lc.setColumn(0, 6, B00100100);
      lc.setColumn(0, 5, B01000010);
      lc.setColumn(0, 4, B10000001);
      lc.setColumn(0, 3, B00000000);
      delay(80);
    }
    else if(i%7 == 5){   //Retracted
      lc.setColumn(3, 0, B00100100);
      lc.setColumn(3, 1, B01000010);
      lc.setColumn(3, 2, B10000001);
      lc.setColumn(3, 3, B00000000);
      lc.setColumn(0, 7, B00100100);
      lc.setColumn(0, 6, B01000010);
      lc.setColumn(0, 5, B10000001);
      lc.setColumn(0, 4, B00000000);
      delay(80);
    }
    else if(i%7 == 6){   //Retracted
      lc.setColumn(3, 0, B01000010);
      lc.setColumn(3, 1, B10000001);
      lc.setColumn(3, 2, B00000000);
      lc.setColumn(0, 7, B01000010);
      lc.setColumn(0, 6, B10000001);
      lc.setColumn(0, 5, B00000000);
      delay(200);
    }
  }
}


void punchScreen(){
  clear();
  showPunch();
  explosion();
  explosion();
}


////////KICK/////////

byte kick[] = 
{
  //K and I
  B01111110,
  B00010000,
  B00101000,
  B01000110,
  B00000000,
  B01000010,
  B01111110,
  B01000010,

  //C and most of K
  B00000000,
  B01111110,
  B01000010,
  B01000010,
  B00000000,
  B01111110,
  B00010000,
  B00101000,

  B01000110
};


void showKick(){
  for(int i=1; i<18; i++){
    lc.setColumn(3-i/8, i%8, kick[i-1]);
  }
}

byte man[] = 
{
  B11101001,
  B11111110,
  B11101001
};

byte flyingMan1[] = 
{
  B11101001,
  B11111110,
  B11101010,
  B00000100
};

byte flyingMan2[] = 
{
  B00000100,
  B11101001,
  B11111110,
  B11101010,
  B00000100,
  B00001000,
  B00010000
};


void flyingKick(){
  
  //Standing man
  for(int i=19; i<22; i++){
    lc.setColumn(3-i/8, i%8, man[i-19]);
  }
  delay(180);

  //Leg up
  //Clear previous line
  lc.setColumn(1, 3, B00000000);
  for(int i=20; i<24; i++){
    lc.setColumn(3-i/8, i%8, flyingMan1[i-20]);
  }

  delay(150);

  //Flying kick
  for(int i=0; i<5; i++){
    //Clear previous line
    lc.setColumn(3-(i+20)/8, (i+20)%8, B00000000);
    for(int j=21; j<27; j++){
      lc.setColumn(3-(j+i)/8, (j+i)%8, flyingMan2[j-21]);
    }
    delay(100);
  }

  //Leg up
  lc.setColumn(0, 1, B00000000);
  lc.setColumn(0, 2, B00000000);
  for(int i=27; i<30; i++){
    lc.setColumn(3-i/8, i%8, flyingMan1[i-27]);
  }
  lc.setColumn(0, 6, B00000000);
  delay(150);

  //Standing man
  lc.setColumn(0, 2, B00000000);
  lc.setColumn(0, 3, B0000000);
  for(int i=28; i<31; i++){
    lc.setColumn(3-i/8, i%8, man[i-28]);
  }

  delay(250);
  
  //Clear man
  for(int i=27; i<31; i++){
    lc.setColumn(3-i/8, i%8, B00000000);
  }
  

}

void kickScreen(){
  clear();
  showKick();
  flyingKick();
}


/////////SCORE////////

byte score[]{
  //S and C
  B00000000,
  B01110010,
  B01010010,
  B01011110,
  B00000000,
  B01111110,
  B01000010,
  B01000010,

  //O and most of R
  B00000000,
  B01111110,
  B01000010,
  B01111110,
  B00000000,
  B01111110,
  B01011000,
  B01010100,

  //little bit of R, E and :
  B01110010,
  B00000000,
  B01111110,
  B01010010,
  B01010010,
  B00000000,
  B01000010,
  B00000000
};

byte zero[]{
  B01111110,
  B01000010,
  B01111110
};

byte one[]{
  B00100010,
  B01111110,
  B00000010
};


byte two[]{
  B01011110,
  B01010010,
  B01110010
};


byte three[]{
  B01010010,
  B01010010,
  B01111110
};


byte four[]{
  B01110000,
  B00010000,
  B01111110
};


byte five[]{
  B01110010,
  B01010010,
  B01011110
};


byte six[]{
  B01111110,
  B00001010,
  B00001110
};


byte seven[]{
  B01000000,
  B01000000,
  B01111110
};


byte eight[]{
  B01111110,
  B01010010,
  B01111110
};


byte nine[]{
  B01110000,
  B01010000,
  B01111110
};


void showScore(){
  for(int i=0; i<24; i++){
    lc.setColumn(3-i/8, i%8, score[i]);
  }
}


void showTens(int num){
  if(num > 99)
    return;

  if(num/10 == 0){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i, zero[i]);
  }
  else if(num/10 == 1){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i, one[i]);
  }
  else if(num/10 == 2){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i, two[i]);
  }
  else if(num/10 == 3){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i, three[i]);
  }
  else if(num/10 == 4){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i, four[i]);
  }
  else if(num/10 == 5){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i, five[i]);
  }
  else if(num/10 == 6){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i, six[i]);
  }
  else if(num/10 == 7){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i, seven[i]);
  }
  else if(num/10 == 8){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i, eight[i]);
  }
  else{
    for(int i=0; i<3; i++)
      lc.setColumn(0, i, nine[i]);
  }
}

void showOnes(int num){
  if(num > 99)
    return;

  if(num%10 == 0){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i+4, zero[i]);
  }
  else if(num%10 == 1){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i+4, one[i]);
  }
  else if(num%10 == 2){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i+4, two[i]);
  }
  else if(num%10 == 3){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i+4, three[i]);
  }
  else if(num%10 == 4){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i+4, four[i]);
  }
  else if(num%10 == 5){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i+4, five[i]);
  }
  else if(num%10 == 6){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i+4, six[i]);
  }
  else if(num%10 == 7){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i+4, seven[i]);
  }
  else if(num%10 == 8){
    for(int i=0; i<3; i++)
      lc.setColumn(0, i+4, eight[i]);
  }
  else{
    for(int i=0; i<3; i++)
      lc.setColumn(0, i+4, nine[i]);
  }
}

void scoreScreen(int score){
  clear();
  showScore();
  showTens(score);
  showOnes(score);
}


////LOSE SCREEN////

byte youLose[] =
{
  B01000000,
  B00100000,
  B00011110,
  B00100000,
  B01000000,
  B00111100,
  B01000010,
  B01000010,

  B00111100,
  B00000000,
  B01111110,
  B00000010,
  B01111110,
  B00000000,
  B00000000,
  B00000000,

  B01111110,
  B00000010,
  B00000010,
  B00000000,
  B00111100,
  B01000010,
  B01000010,
  B00111100,

  B00000000,
  B01110010,
  B01010010,
  B01011110,
  B00000000,
  B01111110,
  B01010010,
  B01000010,
};

byte pathetic[] =
{
  //P and A
  B01111110,
  B01010000,
  B01110000,
  B00000000,
  B01111110,
  B01001000,
  B01111110,
  B00000000,
  
  //T and H
  B01000000,
  B01111110,
  B01000000,
  B00000000,
  B01111110,
  B00010000,
  B01111110,
  B00000000,
  
  //E, T and part of I
  B01111110,
  B01010010,
  B00000000,
  B01000000,
  B01111110,
  B01000000,
  B00000000,
  B01000010,
  
  //Most of I, C, and period
  B01111110,
  B01000010,
  B00000000,
  B01111110,
  B01000010,
  B01000010,
  B00000000,
  B00000010,
};

byte laughable[] =
{
  //L, A, and part of U
  B01111110,
  B00000010,
  B00000000,
  B01111110,
  B01010000,
  B01111110,
  B00000000,
  B01111110,
  
  //Most of U, G, and part of H
  B00000010,
  B01111110,
  B00000000,
  B01111110,
  B01000010,
  B01001110,
  B00000000,
  B01111110,

  //Most of H, A, and part of B
  B00010000,
  B01111110,
  B00000000,
  B01111110,
  B01010000,
  B01111110,
  B00000000,
  B01111110,

  //Most of B, L, and E
  B01010010,
  B00101100,
  B00000000,
  B01111110,
  B00000010,
  B00000000,
  B01111110,
  B01010010
};

byte abysmal[] =
{
  //A and B
  B01111110,
  B01010000,
  B01111110,
  B00000000,
  B01111110,
  B01010010,
  B01010010,
  B00101100,
  
  //Y and part of S
  B00000000,
  B01000000,
  B00100000,
  B00011110,
  B00100000,
  B01000000,
  B00000000,
  B01110010,
  
  //Most of S and M
  B01010010,
  B01011110,
  B00000000,
  B01111110,
  B00100000,
  B00010000,
  B00100000,
  B01111110,
  
  //A and L
  B00000000,
  B01111110,
  B01010000,
  B01111110,
  B00000000,
  B01111110,
  B00000010,
  B00000010
};

void showBoo(){
  int randNum = random(0,3);
  for(int i=0; i<32; i++){
    if(randNum == 1)
      lc.setColumn(3-i/8, i%8, pathetic[i]);
    else if(randNum == 2)
      lc.setColumn(3-i/8, i%8, abysmal[i]);
    else
      lc.setColumn(3-i/8, i%8, laughable[i]);
  }
}

void showLose(){
  for(int i=0; i<32; i++){
    lc.setColumn(3-i/8, i%8, youLose[i]);
  }
}

void glitch(){
  for(int count = 0; count < 5; count++){
    for(int row=0; row<8; row++){
      for(int addr = 0; addr<4; addr++)
        for(int pixel=0; pixel<8; pixel++){
          int randNum = random(0,4);
          lc.setLed(addr, row, pixel, randNum);
        }
    }
  }
}


void loseScreen(){

  clear();

  //Transition Screen//
  glitch();
  
  showBoo();
  delay(1500);
  showLose();
  delay(1500);
  clear();
}



////////WIN////////


byte sublime[] = 
{
  //S and U
  B00000000,
  B01110010,
  B01010010,
  B01011110,
  B00000000,
  B01111110,
  B00000010,
  B01111110,
  
  //B and most of L
  B00000000,
  B01111110,
  B01010010,
  B01010010,
  B00101100,
  B00000000,
  B01111110,
  B00000010,
  
  //Part of L, I, and half of M
  B00000010,
  B00000000,
  B01000010,
  B01111110,
  B01000010,
  B00000000,
  B01111110,
  B00100000,
  
  //Half of M and E
  B00010000,
  B00100000,
  B01111110,
  B00000000,
  B01111110,
  B01010010,
  B01010010,
  B00000000
};

byte hooray[] =
{
  //H and O
  B00000000,
  B01111110,
  B00010000,
  B01111110,
  B00000000,
  B01111110,
  B01000010,
  B01111110,

  //O and most of R
  B00000000,
  B01111110,
  B01000010,
  B01111110,
  B00000000,
  B01111110,
  B01011000,
  B01010100,
  
  //Bit of R, A, and half of Y
  B01110010,
  B00000000,
  B01111110,
  B01010000,
  B01111110,
  B00000000,
  B01000000,
  B00100000,
  
  //Half of Y and !
  B00011110,
  B00100000,
  B01000000,
  B00000000,
  B00000000,
  B01111010,
  B00000000,
  B00000000,
};

byte cheeky[] =
{
  //C and H
  B00000000,
  B01111110,
  B01000010,
  B01000010,
  B00000000,
  B01111110,
  B00010000,
  B01111110,

  //Both E's
  B00000000,
  B01111110,
  B01010010,
  B01010010,
  B00000000,
  B01111110,
  B01010010,
  B01010010,
  
  //K and half of Y
  B00000000,
  B01111110,
  B00010000,
  B00101000,
  B01000110,
  B00000000,
  B01000000,
  B00100000,
  
  //Half of Y and !
  B00011110,
  B00100000,
  B01000000,
  B00000000,
  B00000000,
  B01111010,
  B00000000,
  B00000000,
};

byte blimey[] =
{
  //B and most of L
  B00000000,
  B01111110,
  B01010010,
  B01010010,
  B00101100,
  B00000000,
  B01111110,
  B00000010,

  //part of L, I, and half of M
  B00000010,
  B00000000,
  B01000010,
  B01111110,
  B01000010,
  B00000000,
  B01111110,
  B00100000,

  //Half of M and E
  B00010000,
  B00100000,
  B01111110,
  B00000000,
  B01111110,
  B01010010,
  B01010010,
  B00000000,
  
  //Y and !
  B01000000,
  B00100000,
  B00011110,
  B00100000,
  B01000000,
  B00000000,
  B01111010,
  B00000000,
};

byte youWin[] =
{
  //Y and part of O
  B00000000,
  B01000000,
  B00100000,
  B00011110,
  B00100000,
  B01000000,
  B00000000,
  B01111110,

  //Most of O and U
  B01000010,
  B01111110,
  B00000000,
  B01111110,
  B00000010,
  B01111110,
  B00000000,
  B00000000,
  
  //W and part of I
  B00000000,
  B01111110,
  B00000010,
  B00011110,
  B00000010,
  B01111110,
  B00000000,
  B01000010,
  
  //Most of I and N
  B01111110,
  B01000010,
  B00000000,
  B01111110,
  B00100000,
  B00010000,
  B01111110,
  B00000000
};

void showCongrats(){
  int randNum = random(0,4);
  for(int i=0; i<32; i++){
    if(randNum == 0)
      lc.setColumn(3-i/8, i%8, sublime[i]);
    else if(randNum == 1)
      lc.setColumn(3-i/8, i%8, hooray[i]);
    else if (randNum == 2)
      lc.setColumn(3-i/8, i%8, cheeky[i]);
    else
      lc.setColumn(3-i/8, i%8, blimey[i]);
  }
}

void showWin(){
  for(int i=0; i<32; i++){
    lc.setColumn(3-i/8, i%8, youWin[i]);
  }
}

void winScreen(){
  
  clear();
  //Transition screeen
  glitch();
  
  showCongrats();

  delay(1000);

  clear();
  showWin();

  delay(1000);

  clear();
}


void setup()
{
  lc.shutdown(0,false);  // Wake up displays
  lc.shutdown(1,false);
  lc.shutdown(2,false);
  lc.shutdown(3,false);
  lc.setIntensity(0,5);  // Set intensity levels
  lc.setIntensity(1,5);
  lc.setIntensity(2,5);
  lc.setIntensity(3,5);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
}


void loop()
{
  //loadingScreen();
  //startScreen();
  //punchScreen();
  //kickScreen();
  //dodgeScreen();

  

  //int randNum = random(0,100);

  /*for(int i=0; i<10; i++){
    loseScreen();
    scoreScreen(i);
    delay(1000);
  }*/
  

  /*for(int i=0; i<10; i++){
    winScreen();
    scoreScreen(i);
    delay(1000);
  }*/
  


}