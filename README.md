# Integracja ESP32-S3 ze środowiskiem MQTT
> Celem projektu było zaprogramowanie ESP32-S3 w taki sposób aby łączyło się ono z brokerem MQTT. Za pomocą strony internetowej wysyłano polecenia, które były wykonywane przez ESP.
 
 ![Website](/img/esp32-s3.png "website")

## Project requirements
- Eclipse Mosquitto [2.0.18](https://github.com/eclipse-mosquitto/mosquitto)
- [platformIO](https://github.com/platformio)
- ESP32-S3



## Project Setup

```sh
cd ../website\mqtt_website
```

```sh
npm install
```

### Compile and Hot-Reload for Development

```sh
npm run dev
```

### Type-Check, Compile and Minify for Production

```sh
npm run build
```
