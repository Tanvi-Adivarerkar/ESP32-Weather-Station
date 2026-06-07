  #include <WiFi.h>
  #include <WebServer.h>
  #include <HTTPClient.h>
  #include <ArduinoJson.h>

  // Replace with your network credentials
  const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_PASSWORD";
const char* apiKey = "YOUR_API_KEY";

  // Create a web server on port 80
  WebServer server(80);

  void setup() {
    Serial.begin(115200);  // Connect to Wi-Fi
    // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);

  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < 20) {
    delay(500);
    Serial.print(".");
    attempt++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
  } else {
    Serial.println("");
    Serial.println("Failed to connect to WiFi.");
  }

    // Define the web server routes
    server.on("/", HTTP_GET, handleRoot);
    server.on("/getLocation", HTTP_POST, handleLocation);
    
    // Start the server
    server.begin();
    Serial.println("Server started");
  }

  void loop() {
    // Handle client requests
    server.handleClient();
  }

  void handleRoot() {
    String html = "<html><body><h1>Enter City or Area Name</h1>";
    html += "<form action=\"/getLocation\" method=\"post\">";
    html += "<input type=\"text\" name=\"location\">";
    html += "<input type=\"submit\" value=\"Get Location\">";
    html += "</form></body></html>";
    server.send(200, "text/html", html);
  }

  void handleLocation() {
    if (server.hasArg("location")) {
      String location = server.arg("location");
      String lat, lon;
      if (getCoordinates(location, lat, lon)) {
        String weatherData;
        if (getWeather(lat, lon, weatherData)) {
          server.send(200, "text/html", weatherData);
        } else {
          server.send(500, "text/html", "<html><body><h1>Error retrieving weather data</h1><a href=\"/\">Back</a></body></html>");
        }
      } else {
        server.send(500, "text/html", "<html><body><h1>Error retrieving location coordinates</h1><a href=\"/\">Back</a></body></html>");
      }
    } else {
      server.send(400, "text/html", "<html><body><h1>Invalid request</h1><a href=\"/\">Back</a></body></html>");
    }
  }

  bool getCoordinates(String location, String &lat, String &lon) {
    WiFiClient client;
    HTTPClient http;
    String url = "http://api.openweathermap.org/data/2.5/weather?q=" + location + "&appid=" + apiKey;
    http.begin(client, url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
      
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload); 
      if (doc["coord"]["lat"] && doc["coord"]["lon"]) {
        lat = String(doc["coord"]["lat"].as<float>(), 6);
        lon = String(doc["coord"]["lon"].as<float>(), 6);
        http.end();
        return true;
      } else {
        Serial.println("Error parsing JSON");
      }
    } else {
      Serial.println("Error on HTTP request");
    }
    http.end();
    return false;
  }

  bool getWeather(String lat, String lon, String &weatherData) {
    WiFiClient client;
    HTTPClient http;

    String url = "http://api.openweathermap.org/data/2.5/weather?lat=" + lat + "&lon=" + lon + "&appid=" + apiKey + "&units=metric";
    http.begin(client, url);
    
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
      
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      
      if (doc.containsKey("main") && doc.containsKey("weather") && doc.containsKey("wind")) {
        float temp = doc["main"]["temp"];
        int humidity = doc["main"]["humidity"];
        String description = doc["weather"][0]["description"].as<String>();
        float windSpeed = doc["wind"]["speed"];       
        // Construct HTML response with weather data
        weatherData = "<html><body><h1>Weather in this Location</h1>";
        weatherData += "<p>Temperature: " + String(temp, 1) + " &#8451;</p>";
        weatherData += "<p>Humidity: " + String(humidity) + " %</p>";
        weatherData += "<p>Description: " + description + "</p>";
        weatherData += "<p>Wind Speed: " + String(windSpeed) + " m/s</p>";
        weatherData += "<a href=\"/\">Back</a></body></html>";
        
        http.end();
        return true;
      } else {
        Serial.println("Error parsing JSON for weather data");
      }
    } else {
      Serial.println("Error on HTTP request for weather data");
    }
    
    http.end();
    return false;
  }
