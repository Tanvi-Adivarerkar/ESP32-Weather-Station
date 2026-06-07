# ESP32 Weather Station

An IoT-based weather monitoring system built using ESP32 and OpenWeatherMap API. The system fetches real-time weather information from the internet and displays it through a web server hosted on the ESP32.

## Features

* Real-time weather monitoring
* Temperature display
* Humidity display
* Wind speed information
* Weather description
* Web-based user interface
* Location-based weather search

## Technologies Used

* ESP32
* Arduino IDE
* WiFi Library
* WebServer Library
* HTTPClient Library
* ArduinoJson
* OpenWeatherMap API

## Project Structure

* Weather_web.ino → Main Arduino program
* Weather_webserver_documentation.docx → Project documentation
* screenshots/ → Output screenshots

## How It Works

1. ESP32 connects to a Wi-Fi network.
2. User enters a city name on the web page.
3. ESP32 sends a request to OpenWeatherMap API.
4. Weather data is received in JSON format.
5. ESP32 extracts the required information.
6. Weather details are displayed on the web page.

## Future Improvements

* OLED/LCD display support
* Weather forecast for upcoming days
* Mobile application integration
* Data logging and storage
* Multiple city comparison

## Output Screenshot

<img width="430" height="411" alt="Screenshot 2026-06-07 130629" src="https://github.com/user-attachments/assets/cf3e6be9-a256-44f4-a428-c06e1f6eb0e7" />


## Author

Tanvi Tukaram Adivarekar
