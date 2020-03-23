# BMDatalogger

The BMDatalogger is made to datalog BMTune and Ectune ISR V3 protocol with the Adruino Nano. This is kind of a 'Tuner View' but under Arduino.


# [BUY BMDATALOGGER][]


# Download : [HERE][]


# How to setup BT adater :

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

# Commands for 'Slave' BT Adapter :

1. AT +RMAAD (To clear any paired devices)
2. AT +ROLE=0 (To set it as slave)
3. AT +NAME="YOUR WANTED NAME" (To change the Adapter Name)
4. AT +UART=38400,0,0 (To fix the baud rate at 38400)
5. AT +ADDR (To get the address of this HC-05, NOTE THIS ADDRESS) 
    
# Commands for 'Master' BT Adapter :

1. AT +RMAAD (To clear any paired devices)
2. AT +ROLE=1 (To set it as master if its not already)
3. AT +NAME="YOUR WANTED NAME" (To change the Adapter Name)
4. AT +CMODE=0 (To connect the module to the specified Bluetooth address)
5. AT +BIND=xxxx,xx,xxxxxx (auto connect the module to the specified slave module)
6. AT +UART=38400,0,0 (To fix the baud rate at 38400)

# Donations :

You can donate to me using [This Link][].

[This Link]: <https://www.paypal.me/bouletmarc>
[HERE]: <https://github.com/bouletmarc/BMDatalogger/archive/master.zip>
[BUY BMDATALOGGER]: <https://bmdevs.fwscheckout.com/product/bmdatalogger>
