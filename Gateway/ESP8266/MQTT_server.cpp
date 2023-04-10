#include "MQTT_server.h"

void on_message(const char* topic, byte* payload, unsigned int length);

void SV_Init(void){
  client.setServer(SERVER_DOMAIN, 1883);
  client.setCallback(on_message);
}

void SV_Connect(void){
    if ( !client.connected() ) {
      Serial.print("Connecting to Server ...");
      if ( client.connect(CLIENT_ID, SERVER_USER, SERVER_PASS) ) {
        Serial.println( "[DONE]" );

        // Subscribing channel
        client.subscribe(CHANNEL_COMMAND);
      }
      else {
        Serial.print( "[FAILED] [ rc = " );
        Serial.println( client.state() );
      }
    }
}

bool SV_IsConnected(void){
  return client.connected();
}

void SV_SendData(char* channel, char* json_string){
  Serial.println(json_string);

  client.publish(channel, json_string);
}

// The callback for when a PUBLISH message is received from the server.
void on_message(const char* topic, byte* payload, unsigned int length) {
  char json[length + 1];
  strncpy (json, (char*)payload, length);
  json[length] = '\0';

  Serial.println(json);
}
