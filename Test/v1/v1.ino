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

void loop(){
  if(Bluetooth.available()){
    int intensity = 0;
    int red = 0;
    int green = 0;
    int blue = 0;

    char tmp;
    while((tmp = Bluetooth.read()) != '-'){
      Serial.print(tmp);
      Serial.print(" ");
      intensity *= 10;
      intensity += tmp - '0';
      delay(10);
    }
    if((intensity < 0) || (intensity > 255)){
      intensity = 0;
    }
    
    while((tmp = Bluetooth.read()) != '-'){
      Serial.print(tmp);
      Serial.print(" ");
      red *= 10;
      red += tmp - '0';
      delay(10);
    }
    if((red < 0) || (red > 255)){
      red = 0;
    }
    
    while((tmp = Bluetooth.read()) != '-'){
      Serial.print(tmp);
      Serial.print(" ");
      green *= 10;
      green += tmp - '0';
      delay(10);
    }
    if((green < 0) || (green > 255)){
      green = 0;
    }
    
    while(Bluetooth.available() > 0){
      tmp = Bluetooth.read();
      Serial.print(tmp);
      Serial.print(" ");
      blue *= 10;
      blue += tmp - '0';
      delay(10);
    }
    if((blue < 0) || (blue > 255)){
      blue = 0;
    }

    Serial.println("");
    Serial.print("[");
    Serial.print(intensity);
    Serial.print(", ");
    Serial.print(red);
    Serial.print(", ");
    Serial.print(green);
    Serial.print(", ");
    Serial.print(blue);
    Serial.println("]");

    /* Value of intensity [0 - 255] */
    /* https://fastled.io/docs/3.1/class_c_fast_l_e_d.html#a730ba7d967e882b4b893689cf333b2eb */
    FastLED.setBrightness(intensity);

    for(int i = 0;  i < NUM_LEDS; i++){
      leds[0][i] = CRGB(blue, green, red);
      leds[1][i] = CRGB(blue, green, red);
      leds[2][i] = CRGB(blue, green, red);
    }
    FastLED.show();
  }
}
