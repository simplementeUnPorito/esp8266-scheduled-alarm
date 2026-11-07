# Changes 2023 -> 2026 / Cambios 2023 -> 2026

Every change is also marked with `// FIX 2026:` in `scheduled-alarm/`. Line numbers refer to the corrected files; the originals are in `original-2023/`. Command interface, NTP/UTC-3 sync, summer/winter logic, alarm window and LED behaviour are unchanged.

Cada cambio tambien esta marcado con `// FIX 2026:` en `scheduled-alarm/`. Los numeros de linea corresponden a los archivos corregidos; los originales estan en `original-2023/`. La interfaz de comandos, la sincronizacion NTP/UTC-3, la logica de horario de verano/invierno, la ventana de la alarma y el LED no cambian.

| # | File:line (corrected) | English | Espanol |
|---|---|---|---|
| 1 | definitions.h:32-51 | `date` used before declaration (orig. line 32) and `typedef short uint suint` invalid (orig. 39). `date` is now a plain struct with the public fields the rest of the code already uses (day, month, year, hour, min, sec). | `date` se usaba antes de declararse (orig. linea 32) y `typedef short uint suint` es invalido (orig. 39). `date` es ahora un struct simple con los campos publicos que el resto del codigo ya usa. |
| 2 | definitions.h (orig. 42-141) | Removed the unfinished `date`/`time`/`Cdate` classes: `void` constructors, missing `;` and `)` (orig. 63, 91, 132), missing comma in `isDate` (69), `String.at()`, `toInt(String)`, call to nonexistent `isDate`/`isFormat` members. Nothing called them. | Se eliminaron las clases inconclusas `date`/`time`/`Cdate`: constructores `void`, faltan `;` y `)`, falta una coma en `isDate`, `String.at()`, `toInt(String)`, llamadas a miembros inexistentes. Nada las usaba. |
| 3 | definitions.h:53 | `currentDate` global moved after the struct definition (declaration order). | El global `currentDate` se movio despues de la definicion del struct (orden de declaracion). |
| 4 | definitions.h:29 | Help text said `mm/dd`, parser reads `dd/mm` (`isValidSetDate`: first number = day). Text now says `dd/mm`. | La ayuda decia `mm/dd` pero el parser lee `dd/mm`. El texto ahora dice `dd/mm`. |
| 5 | functions.ino:10 | `char flag = timeClient.update()` -> `bool` (the function returns bool). | `char flag = timeClient.update()` -> `bool` (la funcion devuelve bool). |
| 6 | functions.ino:32 | NTP refresh condition `!flag` only updated `currentDate` when no new sync arrived. Now `flag \|\| timeClient.isTimeSet()`: always refreshed from the local NTPClient clock once synced; never uses the 1970 epoch before first sync. | La condicion `!flag` solo actualizaba `currentDate` cuando no habia una sincronizacion nueva. Ahora `flag \|\| timeClient.isTimeSet()`: siempre se refresca desde el reloj local de NTPClient una vez sincronizado; nunca usa la epoca 1970 antes de la primera sincronizacion. |
| 7 | functions.ino:45 | Removed redundant inner `date result` that shadowed the outer one (same values). | Se elimino la redeclaracion interna de `date result` que ocultaba la externa (mismos valores). |
| 8 | functions.ino:67-69 | Added parentheses in `isAValidDate` (-Wparentheses); logic unchanged. | Parentesis en `isAValidDate` (-Wparentheses); logica sin cambios. |
| 9 | functions.ino:268, 283, 286-296 | `command[cindex]=c` cannot grow a `String` (write past the end is discarded), so `command` stayed empty and no command was ever recognised. Now `command+=c`, and `command=""` wherever `cindex` is reset. | `command[cindex]=c` no puede agrandar un `String` (la escritura fuera de rango se descarta), por lo que `command` quedaba vacio y ningun comando se reconocia. Ahora `command+=c` y `command=""` cada vez que se reinicia `cindex`. |
| 10 | functions.ino:385-395 | Debug `Serial.println` calls in `verifyAlarm()` (ran every `loop()` pass, flooding the console) commented out; alarm logic unchanged. | Los `Serial.println` de depuracion en `verifyAlarm()` (se ejecutaban en cada `loop()` y saturaban la consola) se comentaron; la logica de la alarma no cambia. |

Known behaviour kept as is / Comportamiento conservado: command terminator is `
` followed by ``; `addOneHour()` treats 29 February as valid in every year; alarm window bounds are exclusive.

Verification / Verificacion: PlatformIO, board `nodemcuv2`, espressif8266 4.2.1, NTPClient 3.2.1, `secrets.example.h` as `secrets.h`: build SUCCESS, no warnings in the sketch files. Not tested on hardware / No probado en hardware.
