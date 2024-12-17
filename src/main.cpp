#include <WiFi.h>
#include <MQTT.h>
#include <Adafruit_NeoPixel.h>

WiFiClient net;
MQTTClient client;
String topicLED = "esp/led";

#define PIN 48     // Pin do połączania z diodą LED WS2812
#define NUM_LEDS 1 // Liczba diód LED



unsigned long lastMillis = 0;

// Konfiguracja WiFi
const char ssid[] = "ssid";
const char pass[] = "password"; // Hasło do sieci WiFi

// Konfiguracja MQTT
const char mqttClientId[] = "admin-esp"; // Identyfikator klienta MQTT
const char mqttUsername[] = "username";
const char mqttPassword[] = "password"; // Hasło do serwera MQTT
const char mqttIpBroker[] = "ipBroker"; // IP brokera MQTT

Adafruit_NeoPixel pixels(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void connect()
{
  Serial.print("Sprawdzanie WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nPodłączony do WiFi!");

  Serial.print("Łączenie z brokerem MQTT...");
  while (!client.connect(mqttClientId, mqttUsername, mqttPassword))
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nPołączono z brokerem MQTT!");

  client.subscribe(topicLED);
}
int Kodowanie (int R, int G, int B)
{
  int wynik = (R*1000000) + (G * 1000) + (B);
  return wynik;
}
void ustawienieLED (int i)
{
  int R = floor(i / 1000000);
  int G = floor((i % 1000000) / 1000);
  int B  = floor((i%1000));
  pixels.setPixelColor(0, pixels.Color(R, G, B));
  pixels.show();
}

class RGB
{
public:
    unsigned char R;
    unsigned char G;
    unsigned char B;

    RGB(unsigned char r, unsigned char g, unsigned char b)
    {
        R = r;
        G = g;
        B = b;
    }
    bool Equals(RGB rgb)
    {
        return (R == rgb.R) && (G == rgb.G) && (B == rgb.B);
    }
};

static int HexadecimalToDecimal(String hex) {
    int hexLength = hex.length();
    double dec = 0;

    for (int i = 0; i < hexLength; ++i)
    {
        char b = hex[i];

        if (b >= 48 && b <= 57)
            b -= 48;
        else if (b >= 65 && b <= 70)
            b -= 55;

        dec += b * pow(16, ((hexLength - i) - 1));
    }

    return (int)dec;
}

static RGB HexadecimalToRGB(String hex) {
    if (hex[0] == '#') {
        hex.remove(0, 1);
    }

    unsigned char r = (unsigned char)HexadecimalToDecimal(hex.substring(0, 2));
    unsigned char g = (unsigned char)HexadecimalToDecimal(hex.substring(2, 4));
    unsigned char b = (unsigned char)HexadecimalToDecimal(hex.substring(4, 6));

    return RGB(r, g, b);
}

void messageReceived(String &topic, String &payload)
{
  Serial.print("Przychodzące: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.println(payload);
  Serial.println(payload.length());
  if (topic == topicLED)
  {
    if (payload.toInt() == 1)
    {
      pixels.setPixelColor(0, pixels.Color(255, 255, 255)); // Włącz diodę
      pixels.show();
    }
    if (payload.toInt() == 0)
    {
      pixels.clear(); // Wyłącz diody LED
      pixels.show();
    }
    if (payload.length() == 7)
    {
      RGB rgb = HexadecimalToRGB(payload);
      pixels.setPixelColor(0, pixels.Color(rgb.R, rgb.G, rgb.B)); // Włącz diodę
      pixels.show();
      Serial.println(payload);
      delay(0.1);
    }
  }
}
void setup()
{
  Serial.begin(115200);
  Serial.println("Wykonali: Kamil Kryń, Paweł Nowak");
  WiFi.begin(ssid, pass);

  client.begin(mqttIpBroker, net);
  client.onMessage(messageReceived);

  connect();
}

void loop()
{
  client.loop();

  if (!client.connected())
  {
    connect();
  }
}