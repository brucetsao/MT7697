// this program is written by BruceTsao for MTK Link 7697
#include <LWiFi.h>
#include <String.h>

IPAddress  Meip ,Megateway ,Mesubnet ;
String MacAddress ;
byte mac[6];
int status = WL_IDLE_STATUS;     // the Wifi radio's status

void setup() {
	//Initialize serial and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}
    MacAddress = GetWifiMac() ;
    ShowMac() ;
 

}

void loop() {
}
void ShowMac()
{
  
     Serial.print("MAC:");
     Serial.print(MacAddress);
     Serial.print("\n");

}




String GetWifiMac()
{
   String tt ;
    String t1,t2,t3,t4,t5,t6 ;
    WiFi.status();    //this method must be used for get MAC
  WiFi.macAddress(mac);
  
  Serial.print("Mac:");
   Serial.print(mac[0],HEX) ;
   Serial.print("/");
   Serial.print(mac[1],HEX) ;
   Serial.print("/");
   Serial.print(mac[2],HEX) ;
   Serial.print("/");
   Serial.print(mac[3],HEX) ;
   Serial.print("/");
   Serial.print(mac[4],HEX) ;
   Serial.print("/");
   Serial.print(mac[5],HEX) ;
   Serial.print("~");
   
   t1 = print2HEX((int)mac[0]);
   t2 = print2HEX((int)mac[1]);
   t3 = print2HEX((int)mac[2]);
   t4 = print2HEX((int)mac[3]);
   t5 = print2HEX((int)mac[4]);
   t6 = print2HEX((int)mac[5]);
 tt = (t1+t2+t3+t4+t5+t6) ;
Serial.print(tt);
Serial.print("\n");
  
  return tt ;
}
String  print2HEX(int number) {
  String ttt ;
  if (number >= 0 && number < 16)
  {
    ttt = String("0") + String(number,HEX);
  }
  else
  {
      ttt = String(number,HEX);
  }
  return ttt ;
}



