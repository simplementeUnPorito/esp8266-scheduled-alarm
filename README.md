<p align="center"><img src="docs/img/banner.svg" width="100%" alt="ESP8266 Scheduled Alarm"></p>

<p align="center"><img src="https://img.shields.io/badge/Year-2023-555"> <img src="https://img.shields.io/badge/ESP8266-NodeMCU-1f6feb"> <img src="https://img.shields.io/badge/NTP-time%20sync-informational"> <img src="https://img.shields.io/badge/Arduino-C%2B%2B-orange"> <img src="https://img.shields.io/badge/EasyEDA-PCB-informational"> <img src="https://img.shields.io/badge/License-MIT-lightgrey"></p>
<p align="center"><a href="#english">English</a> · <a href="#español">Español</a></p>

## English

### Overview
This alarm controller uses an ESP8266 (NodeMCU) to obtain wall-clock time from an NTP server over Wi-Fi, apply a user-defined daylight-saving window, and switch an output on and off on a daily schedule. A text command interface on the serial port handles run-time configuration. The custom EasyEDA board carries the NodeMCU, an RTC module, PIR sensors, a relay, a buzzer and battery backup.

### Features
- Time from `pool.ntp.org` via the `NTPClient` library, fixed offset UTC-3 (`-10800 s`).
- Daylight-saving (summer time) handled by two configurable dates; one hour is added while the current date is inside the summer period, with day/month/year rollover.
- Daily alarm window defined by an ON and an OFF time; windows crossing midnight are supported. The output is the on-board LED (active low).
- Automatic Wi-Fi reconnection in the main loop (20 attempts of 500 ms at start-up).
- Input validation with distinct messages for invalid and non-numerical dates/times.

Serial interface (115200 baud). Values use `/` as separator and two digits per field:

| Command | Effect |
|---------|--------|
| `set st DD/MM` | Start date of summer time (the code reads the first field as day and the second as month, although the built-in help text says `mm/dd`) |
| `set wt DD/MM` | Start date of winter time |
| `set alarm_ON hh/mm` | Alarm switch-on time |
| `set alarm_OFF hh/mm` | Alarm switch-off time |
| `led ON` / `led OFF` | Manual LED control; disables the schedule until reset |
| `help` | Prints the command list (in Spanish) |

### How time sync and DST handling work
1. `updateTime()` runs on every loop: it reads the NTP client (epoch time, converted with `gmtime` for day, month and year) into a `currentDate` record.
2. If both summer and winter start dates are set and different, `isSummerTime()` compares the current day/month with them. If the winter date comes before the summer date in the calendar (southern-hemisphere case), summer time applies outside the winter-to-summer interval; otherwise it applies between the summer and winter dates.
3. When summer time applies, `addOneHour()` advances the hour and propagates the carry to day, month and year.
4. `verifyAlarm()` compares hour and minute with the ON/OFF pair (also wrapping past midnight) and drives the LED. The alarm stays off until both times are set.

### Hardware
Parts as placed in the EasyEDA design:

| Component | Role |
|-----------|------|
| NodeMCU V2 (ESP8266) | Wi-Fi, NTP client, command interface |
| DS3231 RTC module | Real-time clock footprint on the board |
| 3x AM312 PIR sensors | Motion-sensor inputs |
| 3x LEDs with 330 Ω resistors | Indicators |
| 2N2222 transistor + buzzer | Audible output |
| Relay module | Switched output |
| AC-DC 5 V module, TP4056 charger, 18650 holder | Mains supply and battery backup |
| 2 push-button headers with resistors | User inputs |

The firmware in this repository uses the NTP time source and the on-board LED only; the PIR sensors, RTC, relay and buzzer are on the board but not driven by this sketch.

### PCB
<p align="center"><img src="hardware/pcb/pcb-top.png" width="460" alt="PCB top view"> <img src="hardware/pcb/pcb-bottom.png" width="460" alt="PCB bottom view"></p>

Previews are rendered from the EasyEDA Standard sources in `hardware/easyeda/`. See [`hardware/pcb/README.md`](hardware/pcb/README.md).

### Demo videos
<p align="center"><a href="https://www.youtube.com/watch?v=4bDRZ9czwoo"><img src="https://img.youtube.com/vi/4bDRZ9czwoo/mqdefault.jpg" width="320" alt="Demo 1"></a> <a href="https://www.youtube.com/watch?v=xoXKMs6CwGw"><img src="https://img.youtube.com/vi/xoXKMs6CwGw/mqdefault.jpg" width="320" alt="Demo 2"></a><br><sub>Demo 1 · Demo 2 (2023)</sub></p>

### Repository layout
```
firmware/scheduled-alarm/   Corrected 2026 Arduino sketch (.ino) and headers
firmware/original-2023/     Original sources as archived (did not compile)
  secrets.example.h         Wi-Fi credentials template (copy to secrets.h)
hardware/easyeda/           EasyEDA Standard sources (schematic, two PCB revisions)
hardware/pcb/               PCB previews
```

### Getting started
1. Install the Arduino IDE with the ESP8266 board package; select a NodeMCU 1.0 (ESP-12E) board.
2. Install the `NTPClient` library (ESP8266WiFi and WiFiUdp ship with the core).
3. Copy `firmware/scheduled-alarm/secrets.example.h` to `secrets.h` and fill in `WIFI_SSID` and `WIFI_PASSWORD` (`secrets.h` is git-ignored).
4. Upload, open the serial monitor at 115200 baud and type `help`.

Note: `firmware/scheduled-alarm/` is the corrected 2026 version (compiles; verified with PlatformIO, nodemcuv2); `firmware/original-2023/` is the original as archived (did not compile). See `firmware/CHANGES.md`. The command terminator expected by `readCommand()` is `\n` followed by `\r`.

### Credits
Designed and developed by Elías Álvarez at Universidad Católica "Nuestra Señora de la Asunción" (Paraguay), 2023.

### License
MIT, see [LICENSE](LICENSE).

---

## Español

### Descripción
Este controlador de alarma usa un ESP8266 (NodeMCU) para obtener la hora de un servidor NTP por Wi-Fi, aplicar una ventana de horario de verano definida por el usuario y activar o desactivar una salida según un horario diario. Los comandos de texto por el puerto serie permiten configurarlo en ejecución. La placa diseñada en EasyEDA incluye el NodeMCU, un módulo RTC, sensores PIR, un relé, un buzzer y respaldo de batería.

### Características
- Hora desde `pool.ntp.org` con la librería `NTPClient`, desfase fijo UTC-3 (`-10800 s`).
- Horario de verano con dos fechas configurables; se suma una hora dentro del período de verano, con acarreo de día/mes/año.
- Ventana diaria de alarma (hora de encendido y apagado), incluso cruzando la medianoche. La salida es el LED integrado (activo en bajo).
- Reconexión Wi-Fi automática en el bucle principal (20 intentos de 500 ms durante el arranque).
- Validación de entradas con mensajes diferentes para fechas/horas inválidas y no numéricas.

Interfaz serie (115200 baudios). Los valores usan `/` como separador y dos dígitos por campo:

| Comando | Efecto |
|---------|--------|
| `set st DD/MM` | Inicio del horario de verano (el código toma el primer campo como día; el texto de ayuda dice `mm/dd`) |
| `set wt DD/MM` | Inicio del horario de invierno |
| `set alarm_ON hh/mm` | Hora de encendido de la alarma |
| `set alarm_OFF hh/mm` | Hora de apagado de la alarma |
| `led ON` / `led OFF` | Control manual del LED; desactiva el horario hasta reiniciar |
| `help` | Imprime la lista de comandos (en español) |

### Sincronización horaria y horario de verano
1. `updateTime()` se ejecuta en cada ciclo: lee el cliente NTP (tiempo epoch, convertido con `gmtime` para obtener día, mes y año) y guarda el resultado en un registro `currentDate`.
2. Si las fechas de inicio de verano e invierno están definidas y son diferentes, `isSummerTime()` las compara con el día y mes actuales. Si la fecha de invierno aparece antes que la de verano en el calendario (caso del hemisferio sur), el horario de verano se aplica fuera del intervalo invierno-verano; en caso contrario, se aplica entre las fechas de verano e invierno.
3. Cuando corresponde el horario de verano, `addOneHour()` adelanta la hora y propaga el acarreo al día, mes y año.
4. `verifyAlarm()` compara la hora y el minuto con el par ON/OFF (incluido el cruce de medianoche) y controla el LED. La alarma permanece apagada hasta que ambas horas estén configuradas.

### Hardware
Componentes tal como se ubicaron en el diseño EasyEDA:

| Componente | Función |
|-----------|------|
| NodeMCU V2 (ESP8266) | Wi-Fi, cliente NTP, interfaz de comandos |
| Módulo RTC DS3231 | Huella para reloj de tiempo real en la placa |
| 3 sensores PIR AM312 | Entradas de detección de movimiento |
| 3 LED con resistencias de 330 Ω | Indicadores |
| Transistor 2N2222 + buzzer | Salida audible |
| Módulo relé | Salida conmutada |
| Módulo AC-DC de 5 V, cargador TP4056, portabatería 18650 | Alimentación de red y respaldo de batería |
| 2 conectores para pulsadores con resistencias | Entradas de usuario |

El firmware de este repositorio utiliza solamente la fuente horaria NTP y el LED integrado; los sensores PIR, el RTC, el relé y el buzzer están presentes en la placa, pero este sketch no los controla.

### PCB
<p align="center"><img src="hardware/pcb/pcb-top.png" width="460" alt="Vista superior de la PCB"> <img src="hardware/pcb/pcb-bottom.png" width="460" alt="Vista inferior de la PCB"></p>

Las vistas previas se generan a partir de las fuentes EasyEDA Standard de `hardware/easyeda/`. Consultar [`hardware/pcb/README.md`](hardware/pcb/README.md).

### Videos de demostración
<p align="center"><a href="https://www.youtube.com/watch?v=4bDRZ9czwoo"><img src="https://img.youtube.com/vi/4bDRZ9czwoo/mqdefault.jpg" width="320" alt="Demostración 1"></a> <a href="https://www.youtube.com/watch?v=xoXKMs6CwGw"><img src="https://img.youtube.com/vi/xoXKMs6CwGw/mqdefault.jpg" width="320" alt="Demostración 2"></a><br><sub>Demostración 1 · Demostración 2 (2023)</sub></p>

### Estructura del repositorio
```
firmware/scheduled-alarm/   Sketch Arduino corregido en 2026 (.ino) y cabeceras
firmware/original-2023/     Fuentes originales tal como se archivaron (no compilaban)
  secrets.example.h         Plantilla de credenciales Wi-Fi (copiar como secrets.h)
hardware/easyeda/           Fuentes EasyEDA Standard (esquemático, dos revisiones de PCB)
hardware/pcb/               Vistas previas de la PCB
```

### Primeros pasos
1. Instalar Arduino IDE con el paquete de placas ESP8266; seleccionar una placa NodeMCU 1.0 (ESP-12E).
2. Instalar la biblioteca `NTPClient` (ESP8266WiFi y WiFiUdp vienen con el core).
3. Copiar `firmware/scheduled-alarm/secrets.example.h` a `secrets.h` y completar `WIFI_SSID` y `WIFI_PASSWORD` (`secrets.h` está ignorado por Git).
4. Cargar el programa, abrir el monitor serie a 115200 baudios y escribir `help`.

Nota: `firmware/scheduled-alarm/` es la versión corregida de 2026 (compila; verificada con PlatformIO, nodemcuv2); `firmware/original-2023/` es el original tal como se archivó (no compilaba). Consultar `firmware/CHANGES.md`. El terminador de comandos que espera `readCommand()` es `\n` seguido de `\r`.

### Créditos
Diseñado y desarrollado por Elías Álvarez en la Universidad Católica "Nuestra Señora de la Asunción" (Paraguay), 2023.

### Licencia
MIT, consultar [LICENSE](LICENSE).
