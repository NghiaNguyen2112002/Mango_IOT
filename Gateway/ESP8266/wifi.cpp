#include "wifi.h"

String list_wf;
// the Wifi radio's status
int status = WL_IDLE_STATUS;


String MakePage(String title, String contents);


void WF_Init(void){
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect();

  WiFi.softAP(WIFI_GATEWAY_NAME, WIFI_GATEWAY_PASS);

  Serial.print("IP ap: "); Serial.println(WiFi.softAPIP());
}

bool WF_IsConnected(void){
  if(WiFi.status() == WL_CONNECTED){
    // Serial.print("IP sta: "); Serial.println(WiFi.localIP());
    return true;
  }

  return false;
}
void WF_Connect(String wifi_name, String wifi_pass){
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(wifi_name, wifi_pass);
  }
}

void WF_Disconnect(void){
  WiFi.disconnect();
}

//=======Webserver for config wifi=========//
void WF_CreateWebserver(void){
  WiFi.disconnect();              //ngat ket noi wifi
  WiFi.softAP(WIFI_GATEWAY_NAME, WIFI_GATEWAY_PASS);
  Serial.println(WiFi.softAPIP());

  int n = WiFi.scanNetworks();
  delay(100);
  list_wf = "";
  
  for (int i = 0; i < n; i++) {    //scan wf and list them
    list_wf += "<option value='";
    list_wf += WiFi.SSID(i);
    list_wf += "'>";
    list_wf += WiFi.SSID(i);
    list_wf += "</option>";
  }

  WebServer.on("/", [](){
    String s = "<h1>Wi-Fi Configuration</h1>";
      s += "<form method='get' action='setap'><label>SSID: </label><select name='wf_name'>";
      s += list_wf;
      s += "Password: <input name='pass' length=64 type='passwod'>";
      s += "<input type='submit'>";
    WebServer.send(200, "text/html", MakePage("Wifi Configuration", s));  
  });

  WebServer.on("/setap", [](){
    _wifi_name = WebServer.arg("wf_name");
    _wifi_pass = WebServer.arg("pass");
    _flag_config_success = true;

    Serial.println(_wifi_name);
    Serial.println(_wifi_pass);
    
    String s = "<h1>Wifi configuration's successful !!</h1>";
    WebServer.send(200, "text/html", MakePage("", s));
  });

  Serial.println("Begin web server");
  WebServer.begin();
}

//==================SUBFUNCTION=============//
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus){
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}


String MakePage(String title, String contents) {
  String s = "<!DOCTYPE html><html><head>";
  s += "<meta name=\"viewport\" content=\"width=device-width,user-scalable=0\">";
  s += "<title>";
  s += title;
  s += "</title></head><body>";
  s += contents;
  s += "</body></html>";
  return s;
}
