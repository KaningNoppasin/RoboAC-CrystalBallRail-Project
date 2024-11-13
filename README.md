# RoboAC-CrystalBallRail-Project
## Project Structure
```
/RoboAC-CrystalBallRail-Project
├── include
├── lib
├── src
│   └── main.cpp
├── platformio.ini
└── README.md
```
- **main.cpp**: Use this file to select which code to execute.
    - Includes and selects between the following modes:
        - `mainMCUcurveSender.ino`: Include this when uploading to the **Curve Machine**.
        - `mainMCUstraightReceiver.ino`: Include this when uploading to the **Straight Machine**.
- ### Curve Machine
  - **main.cpp**
    ```cpp
    #include <Arduino.h>

    #include "./main/mainMCUcurveSender.ino"
    ```
- ### Straight Machine
  - **main.cpp**
    ```cpp
    #include <Arduino.h>

    #include "./main/mainMCUstraightReceiver.ino"
    ```

## Configuration
- ### Arduino Nano
  - **platformio.ini**
    ```ini
    [env:nanoatmega328]
    platform = atmelavr
    board = nanoatmega328
    framework = arduino
    monitor_speed = 115200
    monitor_filters = time, log2file
    lib_deps =
    	waspinator/AccelStepper@^1.64
    	bblanchon/ArduinoJson@^7.0.4
    ```
- ### Arduino Uno
  - **platformio.ini**
    ```ini
    [env:uno]
    platform = atmelavr
    board = uno
    framework = arduino
    monitor_speed = 115200
    monitor_filters = time, log2file
    lib_deps =
    	waspinator/AccelStepper@^1.64
    	bblanchon/ArduinoJson@^7.0.4
    ```