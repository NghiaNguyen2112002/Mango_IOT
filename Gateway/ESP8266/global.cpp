#include "global.h"

WiFiClient espClient = WiFiClient();
PubSubClient client(espClient);
ESP8266WebServer WebServer(80);


String _wifi_name = "MANGDAYKTX H1-518";
String _wifi_pass = "20202024"; 


bool _flag_config_success = false;