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

<img width="792" height="182" alt="Screenshot 2026-06-07 130658" src="https://github.com/user-attachments/assets/2adc484c-22f2-44bc-881b-1f6ea86b844b" />
<img width="430" height="411" alt="Screenshot 2026-06-07 130629" src="https://github.com/user-attachments/assets/f38d5ff0-fb70-4eb7-b8e2-42ef8c4fd72d" />
<img width="431" height="401" alt="Screenshot 2026-06-07 130645" src="https://github.com/user-attachments/assets/b577b898-bf0b-4d8e-b844-b82be6cb254b" />



## Author

Tanvi Tukaram Adivarekar
