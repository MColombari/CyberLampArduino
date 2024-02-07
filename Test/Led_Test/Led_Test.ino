 #include <FastLED.h>
#include <SoftwareSerial.h>

#define NUM_LEDS 24

SoftwareSerial Bluetooth(5,6); //Tx Rx

int Data;
int Max_Intensity = 10;

CRGB leds[3][NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, 9, GBR>(leds[0], NUM_LEDS);
  FastLED.addLeds<WS2812B, 10, GBR>(leds[1], NUM_LEDS);
  FastLED.addLeds<WS2812B, 11, GBR>(leds[2], NUM_LEDS);

  Bluetooth.begin(9600);
  
  
  Serial.begin(9600);
  

}

float x = 0;

void loop(){
  if(Bluetooth.available()){
    Data = 0;
    while(Bluetooth.available() > 0){
      Data *= 10;
      Data += Bluetooth.read() - '0';
      delay(10);
    }
    Serial.println(Data);
    if((Data >= 0) && (Data < 256)){
      Max_Intensity = Data;
    }
  }
  
  float Step = 0;
  for(int i = 0;  i < NUM_LEDS; i++){
    leds[0][i] = CRGB((int)(((sin(x + Step) + 1)) * (Max_Intensity / 2)), (int)(((sin(x + (3,14 / 3) + Step) + 1)) * (Max_Intensity / 2)), (int)(((sin(x + (3,14 * 2 / 3) + Step) + 1)) * (Max_Intensity / 2)));
    
    leds[1][i] = CRGB((int)(((sin(x + Step) + 1)) * (Max_Intensity / 2)), (int)(((sin(x + (3,14 / 3) + Step) + 1)) * (Max_Intensity / 2)), (int)(((sin(x + (3,14 * 2 / 3) + Step) + 1)) * (Max_Intensity / 2)));
    
    leds[2][i] = CRGB((int)(((sin(x + Step) + 1)) * (Max_Intensity / 2)), (int)(((sin(x + (3,14 / 3) + Step) + 1)) * (Max_Intensity / 2)), (int)(((sin(x + (3,14 * 2 / 3) + Step) + 1)) * (Max_Intensity / 2)));
    
    Step += 0.01;
  }
  FastLED.show();
  delay(50);
  x += 0.05;
  if(x > 10000000){
    x = 0;
  }
}
