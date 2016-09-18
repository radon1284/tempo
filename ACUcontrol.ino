#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <SPI.h>
#include <WiFi.h>

int khz = 38;
char ssid[] = "Hotspot";
char pass[] = "12345678";
int controlvar = 0;

int status = WL_IDLE_STATUS;
WiFiServer server(80);
IRsend irsend();

unsigned int hotter[] = {};
unsigned int colder[] = {};
unsigned int ACon[] = {};
unsigned int ACoff[] = {};
unsigned int syson[] = {};
unsigned int sysoff[] = {};
unsigned int sweepon[] = {};
unsigned int sweepoff[] = {};
unsigned int mode1[] = {};
unsigned int mode2[] = {};
unsigned int mode3[] = {};

void setup() {
  Serial.begin(9600);
  delay(10);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  char inString[500];
  if ( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  server.begin();
  irsend.begin();
void loop() {
  WiFiClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true;
    String m = "starthere";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        m = m+c;
        controlvar = (m - 12)/3;
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          if (controlvar == 1){
              irsend.sendRaw(hotter, sizeof(hotter[0]) / sizeof(hotter[0]), khz);   
          }
          if (controlvar == 2){
              irsend.sendRaw(colder, sizeof(colder[0]) / sizeof(colder[0]), khz);   
          }
          if (controlvar == 3){
              irsend.sendRaw(ACon, sizeof(ACon[0]) / sizeof(ACon[0]), khz);   
          }    
          if (controlvar == 4){
              irsend.sendRaw(ACoff, sizeof(ACoff[0]) / sizeof(ACoff[0]), khz);   
          }
          if (controlvar == 5){
              irsend.sendRaw(sweepon, sizeof(sweepon[0]) / sizeof(sweepon[0]), khz);   
          }
          if (controlvar == 6){
              irsend.sendRaw(sweepoff, sizeof(sweepoff[0]) / sizeof(sweepoff[0]), khz);   
          }
          if (controlvar == 7){
              irsend.sendRaw(syson, sizeof(syson[0]) / sizeof(syson[0]), khz);   
          }
          if (controlvar == 8){
              irsend.sendRaw(sysoff, sizeof(sysoff[0]) / sizeof(sysoff[0]), khz);   
          }
          if (controlvar == 9){
              irsend.sendRaw(mode1, sizeof(mode1[0]) / sizeof(mode1[0]), khz);   
          }
          if (controlvar == 10){
              irsend.sendRaw(mode2, sizeof(mode2[0]) / sizeof(mode2[0]), khz);   
          }
          if (controlvar == 11){
              irsend.sendRaw(mode3, sizeof(mode3[0]) / sizeof(mode3[0]), khz);   
          }
          break;
          }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");    
  }
}
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
