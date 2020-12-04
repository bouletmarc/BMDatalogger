# BMDatalogger

The BMDatalogger is made to datalog BMTune, Ectune and HTS (ISR V3 protocol). This is kind of a 'Tuner View/OBD1 Reader'.

# [BUY BMDATALOGGER][]

# Introduction

The BMDatalogger can be used to Display all the engines sensors value you generally found inside your tuning software (BMTune, eCtune or HTS) but at all time in your project car. The BMDatalogger can be installed permanently in the car or used as a handheld device. It can also display Engine Error Code (MIL) and reset the ECU to clear the codes too. The BMDatalogger works with Two(2x) Bluetooth Adapters to communicate with the ECU. One Bluetooth adapter are installed on the BMDatalogger by itself and the other adapter will install in the 4Pin CN2 Slot of the OBD1 ECU, both adapter should be reprogrammed to pair with each other on when Powering them.

__*On the BMDatalogger sold by BMDevs/Bouletmarc, BOTH Bluetooth Adapters are already programmed and ready to be used when receiving your package, you don't need to program them but the guide to program the bluetooth adapters are down bellow*__

# BMDatalogger V3.0 Core

At the moment of writing this guideline, the Lastest BMDatalogger version available are the V3.0! This version now have an Atmega64A core which can make the projects files incompatible for the original Arduino Nano with the Atmega328P core. Severals lines of codes and functions have been added since the original release of the project files that it's taking now all the space of the Arduino Nano and needed something bigger with more space available to fully include the Setup menu and make the LCD Display fully independant of needing a computer to customize the screen and parameters.

# Specifications V3.0+

- ATmega64A Core running at 16Mhz
- CH240 Serial Adapter for communicating with Computer ([Download Driver Here][])
- Can be powered by 5V (USB) or 12V (Input Pin)
- Intefer with the menu with Two(2x) integrated button on the back OR with externals buttons (not included)
- Two(2x) Bluetooth Adapters programmed for the communication between the ECU and the BMDatalogger
- Display all the Engine Sensor datalogs values (Up to 79 kind of sensor data available!)
- Display the Engine Error codes (MIL), can also reset the ECU to attemp clearing the codes
- Integrated setup menu to customize the Diplayed Pages
- Doesn't require a Computer, the BMDatalogger is an independant device
- Differents Pages Presets (Small-Medium-Big Font, Progressbar)

# Tool for updating parameters 

You can download the tool to customize the LCD Display Paremeters [HERE][] for the BMDatalogger that are under V2.0! On the BMDatalogger V2.0 and Greater you DON'T need to download this tool, their is a 'setup' menu integrated to adjust the parameters of the LCD Display at your desire.

# Uploading/Customizing the Code to your device

The 'Arduino' (or .ino files) shared in this project should be used __AT YOUR OWN RISK__ and for personal project only(not for business use). BMDevs/Bouletmarc aren't responsible for any possible damages caused to your device if you intend to use the codes and/or customize it to your desire. You must understand that the Codes are used on an Atmega64A core and that you'll have to find an alternative method to use it with your proper Arduino device.

# How to setup Bluetooth adapter

Most of the HC05 sold on the market are set to 9600 baudrate by default, and they are on 'Master' mode by default. We need to change the Baudrate to 38400 and set ONE of the adapter to 'Slave' mode (automatic connection with the other adapter).

![alt tag](https://raw.githubusercontent.com/bouletmarc/BMDatalogger/master/Bluetooth_setup_diagram.png)

1. Before giving Power, make sure you hold the 'Key Button' to enter in 'Edit' mode.
2. Give Power and Release the button after 2-3s
3. Open Arduino.exe
4. Select the COM Port you are using with the FT232RL
5. Open the COM Port Monitor
6. Change the Monitor Baudrate to '38400'
7. Change the Monitor Lines ending to 'both NL & CR'
8. Type 'AT' and see if it return 'OK'
9. If it return 'OK' follow the step for setting Slave or Master Adapter, otherwise repeat steps

# Commands for 'Slave' BT Adapter:

1. AT +RMAAD (To clear any paired devices)
2. AT +ROLE=0 (To set it as slave)
3. AT +NAME="YOUR WANTED NAME" (To change the Adapter Name)
4. AT +UART=38400,0,0 (To fix the baud rate at 38400)
5. AT +ADDR (To get the address of this HC-05, NOTE THIS ADDRESS) 
    
# Commands for 'Master' BT Adapter:

1. AT +RMAAD (To clear any paired devices)
2. AT +ROLE=1 (To set it as master if its not already)
3. AT +NAME="YOUR WANTED NAME" (To change the Adapter Name)
4. AT +CMODE=0 (To connect the module to the specified Bluetooth address)
5. AT +BIND=xxxx,xx,xxxxxx (auto connect the module to the specified slave module)
6. AT +UART=38400,0,0 (To fix the baud rate at 38400)

# Donations :

You can donate to me using [This Link][].

[Download Driver Here]: <https://sparks.gogo.co.nz/assets/_site_/downloads/CH34x_Install_Windows_v3_4.zip>
[This Link]: <https://www.paypal.me/bouletmarc>
[HERE]: <https://github.com/bouletmarc/BMDatalogger/archive/master.zip>
[BUY BMDATALOGGER]: <https://bmdevs.fwscheckout.com/product/bmdatalogger>
