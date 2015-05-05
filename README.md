Building and flashing the PIC32MZ
---------------------------------

What you need:

  - MPLAB X 2.35
  - xc 1.34
  - Harmony 1.03

Flashing the RN42 Bluetooth module
----------------------------------

When the board is first flashed, the RN42 module must be "flashed" as well.
After powering up, within less than 60 seconds, connect to it with a serial
console over Bluetooth. Type

```
$$$
```

to enter command mode. The module should respond with

```
CMD
```

Then, type

```
ST,254<cr>
```

to disable command mode over UART. The module should respond with

```
AOK
```

Then, type

```
SU,92<cr>
```

to set baud rate to 921K. The module should respond with

```
AOK
```

as before. Finally, exit command mode with

```
---<cr>
```

and reboot the board.
