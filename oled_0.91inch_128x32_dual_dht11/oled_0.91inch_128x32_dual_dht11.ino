#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <DHT.h>

#define DHTPIN 18     // Digital pin connected to the DHT sensor
#define DHTPIN2 19     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 
DHT dht(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

void setup(void) {
   u8g2.begin();
   u8g2.clearBuffer();         // clear the internal memory
   
   u8g2.setFont(u8g2_font_unifont_t_arabic);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(0,14,"Mercedes Benz");  // write something to the internal memory
   u8g2.drawStr(0,31,"     s124"); // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(5000);
   
   dht.begin();
   dht2.begin();
}

void loop(void) {
   u8g2.clearBuffer();					// clear the internal memory
   
   // Reading temperature or humidity takes about 250 milliseconds!
   // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
   float h = dht.readHumidity();
   float h2 = dht2.readHumidity();
  
   // Read temperature as Celsius (the default)
   float t = dht.readTemperature();
   float t2 = dht2.readTemperature();
  
   // Read temperature as Fahrenheit (isFahrenheit = true)
   //float f = dht.readTemperature(true);


   
   char buffer[20];
   char floatbuffer[10];
   
   dtostrf(t,3,1,floatbuffer);
   sprintf(buffer,"%s%s",floatbuffer,"C    ");
   dtostrf(t2,3,1,floatbuffer);
   sprintf(buffer,"%s%sC",buffer,floatbuffer);


   u8g2.clearBuffer();
   u8g2.setFont(u8g2_font_logisoso28_tr);
   u8g2.drawStr(10,30,buffer);
   u8g2.sendBuffer();
   delay(3200);

   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_unifont_t_arabic);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(2,14,"Outside  Inside");  // write something to the internal memory
   u8g2.drawStr(3,31,buffer);
   u8g2.sendBuffer();
   delay(3200);


   u8g2.clearBuffer();
   u8g2.setFont(u8g2_font_unifont_t_arabic);
   u8g2.drawStr(2,14,"Outside  Inside");
   buffer[0] = '\0';
   floatbuffer[0] = '\0';
   dtostrf(h,3,1,floatbuffer);
   sprintf(buffer,"%s%s",floatbuffer,"%    ");
   dtostrf(h2,3,1,floatbuffer);
   sprintf(buffer,"%s%s%%",buffer,floatbuffer);
   u8g2.drawStr(3,31,buffer);
   u8g2.sendBuffer();
   delay(3200);
}
