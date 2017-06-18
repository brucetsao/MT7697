/*
  This example connects to an unencrypted Wifi network.
  Then it prints the  MAC address of the Wifi shield,
  the IP address obtained, and other network details.

  Circuit:
  * LinkIt 7697 HDK

  created 13 July 2010
  by dlf (Metodo2 srl)
  modified 31 May 2012
  by Tom Igoe
  modified 23 May 2017
  by MediaTek Labs
*/
#include <LWiFi.h>
#include "DHT.h"
#define DHTPIN 8     // what digital pin we're connected to
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

char ssid[] = "IOT";     //  your network SSID (name)
char pass[] = "iot12345";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
IPAddress  Meip , Megateway , Mesubnet ;
String MacAddress ;
uint8_t MacData[6];
WiFiServer server(80);

//-----end of wifi use



void setup() {
	//Initialize serial and wait for port to open:
	Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
   
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

  MacAddress = GetWifiMac() ; // get MacAddress
  ShowMac() ;       //Show Mac Address

  // attempt to connect to Wifi network:
  initializeWiFi();
  server.begin();
  // you're connected now, so print out the status:
  ShowInternetStatus();

}// END Setup

static int count = 0;
void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);


  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" % and ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t\n");

  // wifi code here
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client)
  {
    Serial.println("Now Someone Access WebServer");

    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank)
        {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          client.println("<head>");
          client.println("<script type='text/javascript' src='https://www.gstatic.com/charts/loader.js'></script>");
          client.println("<script type='text/javascript'>");
          client.println("google.charts.load('current', {'packages':['gauge']});");
          client.println("google.charts.setOnLoadCallback(drawChart);");
          client.println("  function drawChart() {");
          client.println("var data = google.visualization.arrayToDataTable([['Label', 'Value'],['濕度',");
          client.println(h);
          client.println("],]);");
          client.println(" var options = {width: 300, height: 300,redFrom: 90, redTo: 100,yellowFrom:75, yellowTo: 90,minorTicks: 5};");
          client.println("var chart = new google.visualization.Gauge(document.getElementById('chart_div'));");
          client.println("chart.draw(data, options);");
          client.println("}");
          client.println("</script>");
          client.println("</head>");
          client.println("<meta charset='utf-8'>");
          client.println("<body>");
          client.println("<div id='chart_div' style='width: 300px; height: 300px;'></div>");
          client.println("</body>");
          /*
            client.print("Humidity: ");
            client.print(h);
            client.print(" % and ");
            client.print("Temperature: ");
            client.print(t);
            client.print("*C   and  ");
            client.print(f);
            client.print("*F  (end) ");
            client.println("<br />");
          */
          client.println("</html>");
          break;
        }
        if (c == '\n')
        {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r')
        {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }


    delay(800) ;
} // END Loop


void printWifiData() {
	// print your WiFi shield's IP address:
	IPAddress ip = WiFi.localIP();
	Serial.print("IP Address: ");
	Serial.println(ip);
	Serial.println(ip);

	// print your MAC address:

	WiFi.macAddress(MacData);
	Serial.print("MAC address: ");
	Serial.print(MacData[0], HEX);
	Serial.print(":");
	Serial.print(MacData[1], HEX);
	Serial.print(":");
	Serial.print(MacData[2], HEX);
	Serial.print(":");
	Serial.print(MacData[3], HEX);
	Serial.print(":");
	Serial.print(MacData[4], HEX);
	Serial.print(":");
	Serial.println(MacData[5], HEX);

}

void initializeWiFi() {
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    //   status = WiFi.begin(ssid);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.print("\n Success to connect AP:") ;
  Serial.print(ssid) ;
  Serial.print("\n") ;

}
void printCurrentNet() {
	// print the SSID of the network you're attached to:
	Serial.print("SSID: ");
	Serial.println(WiFi.SSID());

	// print the MAC address of the router you're attached to:
	byte bssid[6];
	WiFi.BSSID(bssid);
	Serial.print("BSSID: ");
	Serial.print(bssid[5], HEX);
	Serial.print(":");
	Serial.print(bssid[4], HEX);
	Serial.print(":");
	Serial.print(bssid[3], HEX);
	Serial.print(":");
	Serial.print(bssid[2], HEX);
	Serial.print(":");
	Serial.print(bssid[1], HEX);
	Serial.print(":");
	Serial.println(bssid[0], HEX);

	// print the received signal strength:
	long rssi = WiFi.RSSI();
	Serial.print("signal strength (RSSI):");
	Serial.println(rssi);

	// print the encryption type:
	byte encryption = WiFi.encryptionType();
	Serial.print("Encryption Type:");
	Serial.println(encryption, HEX);
	Serial.println();
}

void ShowInternetStatus()
{

  if (WiFi.status())
  {
    Meip = WiFi.localIP();
    Serial.print("Get IP is:");
    Serial.print(Meip);
    Serial.print("\n");

  }
  else
  {
    Serial.print("DisConnected:");
    Serial.print("\n");
  }

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
  String t1, t2, t3, t4, t5, t6 ;
  WiFi.status();    //this method must be used for get MAC
  WiFi.macAddress(MacData);

  Serial.print("Mac:");
  Serial.print(MacData[0], HEX) ;
  Serial.print("/");
  Serial.print(MacData[1], HEX) ;
  Serial.print("/");
  Serial.print(MacData[2], HEX) ;
  Serial.print("/");
  Serial.print(MacData[3], HEX) ;
  Serial.print("/");
  Serial.print(MacData[4], HEX) ;
  Serial.print("/");
  Serial.print(MacData[5], HEX) ;
  Serial.print("~");

  t1 = print2HEX((int)MacData[0]);
  t2 = print2HEX((int)MacData[1]);
  t3 = print2HEX((int)MacData[2]);
  t4 = print2HEX((int)MacData[3]);
  t5 = print2HEX((int)MacData[4]);
  t6 = print2HEX((int)MacData[5]);
  tt = (t1 + t2 + t3 + t4 + t5 + t6) ;
  Serial.print(tt);
  Serial.print("\n");

  return tt ;
}
String  print2HEX(int number) {
  String ttt ;
  if (number >= 0 && number < 16)
  {
    ttt = String("0") + String(number, HEX);
  }
  else
  {
    ttt = String(number, HEX);
  }
  return ttt ;
}



