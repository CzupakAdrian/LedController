/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com/esp8266-nodemcu-access-point-ap-web-server/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Hash.h>

const char *ssid = "LED-controller";
const char *password = "1234";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0; // will store last time DHT was updated

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
    <title>LED cotroller</title>
    <script>
        function postIt(command) {
            var request = new XMLHttpRequest();
            request.open("POST", "/function", true);
            request.send(command);
        }
        function onOff() {
            postIt("command=onOff");
        }
        function progChange() {
            postIt("command=progChange");
        }
        function sigmaInc() {
            postIt("command=sigmaInc");
        }
        function simgaDec() {
            postIt("command=sigmaDec");
        }
        function freqInc() {
            postIt("command=freqInc");
        }
        function freqDec() {
            postIt("command=freqDec");
        }
        function intInc() {
            postIt("command=intInc");
        }
        function intDec() {
            postIt("command=intDec");
        }
    </script>
    <style>
        .IO_box {
            float: left;
            margin: 0 20px 20px 0;
            border: 1px solid blue;
            padding: 0 5px 0 5px;
            width: 120px;
        }

        h1 {
            font-size: 120%;
            color: blue;
            margin: 0 0 10px 0;
        }

        button {
            font-size: 80%;
            color: #252525;
        }
    </style>
</head>

<body unload="controlLED()">
    <h1>LED controller</h1><br />
    <h1>%FUNCTION%</h1><br />
    <div class="IO_box">
        <button type="button" id="onOff" onclick="onOff()">ON/OFF</button><br /><br />
        <button type="button" id="progChange" onclick="progChange()">Zmień program</button><br /><br />
        <button type="button" id="sigmaInc" onclick="sigmaInc()">Poszerz</button><br />
        <button type="button" id="sigmaDec" onclick="sigmaDec()">Zwęź</button><br /><br />
        <button type="button" id="freqInc" onclick="freqInc()">Przyspiesz</button><br />
        <button type="button" id="freqDec" onclick="freqDec()">Zwolnij</button><br /><br />
        <button type="button" id="intInc" onclick="intInc()">Rozjaśnij</button><br />
        <button type="button" id="intDec" onclick="intDec()">Zciemnij</button>
    </div>
</body>

</html>)rawliteral";

const char index_html1[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
    <title>LED cotroller</title>
    <style>
        h1 {
            font-size: 120%;
            color: blue;
            margin: 0 0 10px 0;
        }
    </style>
</head>
<body>
    <h1>Brawo</h1>
</body>
</html>)rawliteral";

AsyncWebParameter *command;
String processor(const String &var)
{
    // Serial.println(var);
    if (var == "FUNCTION")
    {
        return command->value();
    }
    return String();
}

void setup()
{
    // Remove the password parameter, if you want the AP (Access Point) to be open
    WiFi.softAP(ssid);

    IPAddress IP = WiFi.softAPIP();

    // Route for root / web page
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) { request->send_P(200, "text/html", index_html); });
    server.on("/function", HTTP_POST, [](AsyncWebServerRequest *request) {
        command = request->getParam("command");
        request->send_P(200, "text/html", index_html1);
    });

    // Start server
    server.begin();
}

void loop()
{
}