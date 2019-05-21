#include <LiquidCrystal.h>
#define ag_ismi "UBY"
#define ag_sifresi "1234qwer"

LiquidCrystal lcd(12,11,5,4,3,2);


void setup()
{
  lcd.begin(16,2);
  lcd.print("GomuluProje");
  
  Serial.begin(115200);
  Serial.println("AT");
  delay(3000);
 
  if(Serial.find("OK")){
     Serial.println("AT+CWMODE=1");
     delay(2000);
     String baglantiKomutu=String("AT+CWJAP=\"")+ag_ismi+"\",\""+ag_sifresi+"\"";
     Serial.println(baglantiKomutu);
     delay(5000);
 }
   Serial.print("AT+CIPMUX=1\r\n");
   delay(200);
   Serial.print("AT+CIPSERVER=1,80\r\n");
   delay(1000);  
}
void loop(){

  int x = 0;
  int bas = 0;
  int son = 0;
  
  if(Serial.available()>0){
    if(Serial.find("+IPD,")){
      String metin = "<head> Isitme Engelliler Icin Proje </head>";
      String cipsend = "AT+CIPSEND=";
      cipsend +="0";
      cipsend +=",";
      cipsend += metin.length();
      cipsend += "\r\n";
      Serial.print(cipsend);
      delay(500);
      Serial.println(metin);
      String gelen ="";
      char serialdenokunan;
      while(Serial.available()>0){
        serialdenokunan = Serial.read();
        gelen +=serialdenokunan;
      }
        gelen.replace("%20", " ");
        gelen.replace("%C3%A7", "c");
        gelen.replace("%C3%87", "C");
        gelen.replace("%C4%9F", "g");
        gelen.replace("%C4%B1", "i");
        gelen.replace("%C4%B0", "I");
        gelen.replace("%C3%B6", "o");
        gelen.replace("%C3%96", "O");
        gelen.replace("%C5%9F", "s");
        gelen.replace("%C5%9E", "S");
        gelen.replace("%C3%BC", "u");
        gelen.replace("%C3%9C", "U");
        
        if(gelen != ""){
          for(int i=0; i<gelen.length(); i++){
            if(gelen.substring(i,i+1) == "/"){
              if(x == 1){
                x = 0;
                son = i-5;
                break;
              }
              else{
                x = 1;
                bas = i+1;
              }
            }
            if(son == 0){
              if(gelen.substring(gelen.length()-1,gelen.length()) == "P")son = gelen.length()-4;
              else if(gelen.substring(gelen.length()-1,gelen.length()) == "T")son = gelen.length()-3;
              else if(gelen.substring(gelen.length()-1,gelen.length()) == "H")son = gelen.length()-1;
              else son = gelen.length();
            }
          }
          Serial.println(gelen);
          lcd.clear();
          if(son-bas > 16){
            lcd.setCursor(0,0);
            lcd.print(gelen.substring(bas,bas+16));
            lcd.setCursor(0,1);
            lcd.print(gelen.substring(bas+16,son));
          }
          else{
            lcd.setCursor(0,0);
            lcd.print(gelen.substring(bas,son));
          }
          
        }
    }
  }
}