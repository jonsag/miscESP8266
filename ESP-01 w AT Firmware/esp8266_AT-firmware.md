# espLogger

An ESP-01 module to handle logging and monitoring of the ardHydroponic.  

## Check firmware version

Hook up your FTDI device to the ESP module.  

    FTDI            ESP-01  
    1 GND   ->      2   GND
    2 CTS   ->
    3 VCC   ->      7   VCC
    4 Tx    ->      8   Rx
    5 Rx    ->      1   Tx
    6 DTR   ->

Check connection with picocom  
>$ picocom -b 115200 /dev/ttyUSB0 --omap crcrlf  

    picocom v2.2

    port is        : /dev/ttyUSB0
    flowcontrol    : none
    baudrate is    : 115200
    parity is      : none
    databits are   : 8
    stopbits are   : 1
    escape is      : C-a
    local echo is  : no
    noinit is      : no
    noreset is     : no
    nolock is      : no
    send_cmd is    : sz -vv
    receive_cmd is : rz -vv -E
    imap is        : 
    omap is        : crcrlf,
    emap is        : crcrlf,delbs,

    Type [C-a] [C-h] to see available commands

    Terminal ready

Check if the ESP is answering  
>AT

    OK  

Check fw version  
>AT+GMR

    AT version:0.25.0.0(Jun  5 2015 16:27:16)
    SDK version:1.1.1
    Ai-Thinker Technology Co. Ltd.
    Jun 23 2015 23:23:50

    OK

Exit program  
>$ Ctrl+a Ctrl+x  

## Update firmware

Install tool  
>$ pip install esptool

Pull GPIO0 to ground and start the ESP via the FTDI.  
Also make sure you got a solid 3.3V source as the chip will not boot properly otherwise.  

### Source from aprbrother  

Download firmware from [http://wiki.aprbrother.com/wiki/Firmware_For_ESP8266](http://wiki.aprbrother.com/wiki/Firmware_For_ESP8266).  
>$ wget https://i1.aprbrother.com/ai-thinker-v1.1.1.bin  

Flash firmware  
>$ esptool.py -p /dev/ttyUSB0 -b 115000 write_flash 0x000000 ai-thinker-v1.1.1.bin  

    esptool.py v3.0
    Serial port /dev/ttyUSB0
    Connecting....
    Detecting chip type... ESP8266
    Chip is ESP8266EX
    Features: WiFi
    Crystal is 26MHz
    MAC: e8:db:84:dc:4e:77
    Uploading stub...
    Running stub...
    Stub running...
    Configuring flash size...
    Compressed 1044480 bytes to 204643...
    Wrote 1044480 bytes (204643 compressed) at 0x00000000 in 18.2 seconds (effective 459.2 kbit/s)...
    Hash of data verified.

    Leaving...
    Hard resetting via RTS pin...

### Get AT sources from EspressIF

[https://www.espressif.com/en/support/download/at?keys=&field_type_tid%5B%5D=799](https://www.espressif.com/en/support/download/at?keys=&field_type_tid%5B%5D=799)  

Look for ESP8266 NonOS AT Bin, download and extract it  

### Source from espressif, ESP8266 NonOS AT Bin v1.7.4  
  
>$ wget https://www.espressif.com/sites/default/files/ap/ESP8266_NonOS_AT_Bin_V1.7.4.zip  
>$ unzip ESP8266_NonOS_AT_Bin_V1.7.4.zip  
>$ cd ESP8266_NonOS_AT_Bin_V1.7.4/bin/  

Find out how to upload it  
>$ cat at/README.md

    ...
    ### Flash size 8Mbit: 512KB+512KB
        boot_v1.2+.bin              0x00000
        user1.1024.new.2.bin        0x01000
        esp_init_data_default.bin   0xfc000
        blank.bin                   0x7e000 & 0xfe000
    ...

Flash chip  
>$ esptool.py -p /dev/ttyUSB0 -b 74880 write_flash --flash_size 1MB --flash_freq 26m 0x00000 boot_v1.7.bin 0x01000 at/512+512/user1.1024.new.2.bin 0xFC000 esp_init_data_default_v08.bin 0x7E000 blank.bin 0xFE000 blank.bin

Or with fewer options  
>$ esptool.py -p /dev/ttyUSB0 write_flash 0x00000 boot_v1.7.bin 0x01000 at/512+512/user1.1024.new.2.bin 0xFC000 esp_init_data_default_v08.bin 0x7E000 blank.bin 0xFE000 blank.bin  

    esptool.py v3.0
    Serial port /dev/ttyUSB0
    Connecting....
    Detecting chip type... ESP8266
    Chip is ESP8266EX
    Features: WiFi
    Crystal is 26MHz
    MAC: e8:db:84:dc:4e:77
    Uploading stub...
    Running stub...
    Stub running...
    Configuring flash size...
    Compressed 4080 bytes to 2936...
    Wrote 4080 bytes (2936 compressed) at 0x00000000 in 0.4 seconds (effective 78.4 kbit/s)...
    Hash of data verified.
    Compressed 413444 bytes to 296966...
    Wrote 413444 bytes (296966 compressed) at 0x00001000 in 40.4 seconds (effective 81.8 kbit/s)...
    Hash of data verified.
    Compressed 128 bytes to 75...
    Wrote 128 bytes (75 compressed) at 0x000fc000 in 0.0 seconds (effective 32.0 kbit/s)...
    Hash of data verified.
    Compressed 4096 bytes to 26...
    Wrote 4096 bytes (26 compressed) at 0x0007e000 in 0.0 seconds (effective 2052.6 kbit/s)...
    Hash of data verified.
    Compressed 4096 bytes to 26...
    Wrote 4096 bytes (26 compressed) at 0x000fe000 in 0.0 seconds (effective 2034.8 kbit/s)...
    Hash of data verified.

    Leaving...
    Hard resetting via RTS pin...

Firmware check in serial monitor  
>AT+GMR

    AT version:1.7.4.0(May 11 2020 19:13:04)
    SDK version:3.0.4(9532ceb)
    compile time:May 27 2020 10:12:17
    Bin version(Wroom 02):1.7.4
    OK

### Source from espressif, ESP8266 NonOS AT Bin v1.6.2  

Get source  
>$ wget wget https://www.espressif.com/sites/default/files/ap/ESP8266_AT_Bin_V1.6.2_0.zip  
>$ unzip ESP8266_AT_Bin_V1.6.2_0.zip  
>$ cd ESP8266_AT_Bin_V1.6.2/bin/  

Find out how to upload it  
>$ cat at/README.md

    ...
    ### Flash size 8Mbit: 512KB+512KB
        boot_v1.2+.bin              0x00000
        user1.1024.new.2.bin        0x01000
        esp_init_data_default.bin   0xfc000 (optional)
        blank.bin                   0x7e000 & 0xfe000
    ...

Flash chip  
>$ esptool.py -p /dev/ttyUSB0 -b 74880 write_flash --flash_size 1MB --flash_freq 26m 0x00000 boot_v1.7.bin 0x01000 at/512+512/user1.1024.new.2.bin 0xFC000 esp_init_data_default_v08.bin 0x7E000 blank.bin 0xFE000 blank.bin

    esptool.py v3.0
    Serial port /dev/ttyUSB0
    Connecting....
    Detecting chip type... ESP8266
    Chip is ESP8266EX
    Features: WiFi
    Crystal is 26MHz
    MAC: e8:db:84:dc:4e:77
    Uploading stub...
    Running stub...
    Stub running...
    Configuring flash size...
    Compressed 4080 bytes to 2936...
    Wrote 4080 bytes (2936 compressed) at 0x00000000 in 0.4 seconds (effective 78.3 kbit/s)...
    Hash of data verified.
    Compressed 408388 bytes to 293527...
    Wrote 408388 bytes (293527 compressed) at 0x00001000 in 40.1 seconds (effective 81.5 kbit/s)...
    Hash of data verified.
    Compressed 128 bytes to 75...
    Wrote 128 bytes (75 compressed) at 0x000fc000 in 0.0 seconds (effective 32.6 kbit/s)...
    Hash of data verified.
    Compressed 4096 bytes to 26...
    Wrote 4096 bytes (26 compressed) at 0x0007e000 in 0.0 seconds (effective 2048.4 kbit/s)...
    Hash of data verified.
    Compressed 4096 bytes to 26...
    Wrote 4096 bytes (26 compressed) at 0x000fe000 in 0.0 seconds (effective 2175.0 kbit/s)...
    Hash of data verified.

    Leaving...
    Hard resetting via RTS pin...

Firmware check in serial monitor  
>AT+GMR

    AT version:1.6.2.0(Apr 13 2018 11:10:59)
    SDK version:2.2.1(6ab97e9)
    compile time:Jun  7 2018 19:34:26
    Bin version(Wroom 02):1.6.2
    OK

### Source from espressif, ESP8266 NonOS AT Bin v1.5.1  

Get source  
>$ wget wget https://www.espressif.com/sites/default/files/ap/esp8266_at_bin_v1.5.1.zip  
>$ unzip esp8266_at_bin_v1.5.1.zip  
>$ cd ESP8266_AT_Bin_V1.5.1/bin  

Find out how to upload it  
>$ cat at/README.md

    ...
    ### Flash size 8Mbit: 512KB+512KB
        boot_v1.2+.bin              0x00000
        user1.1024.new.2.bin        0x01000
        esp_init_data_default.bin   0xfc000 (optional)
        blank.bin                   0x7e000 & 0xfe000
    ...

Flash chip  
>$ esptool.py -p /dev/ttyUSB0 -b 74880 write_flash --flash_size 1MB --flash_freq 26m 0x00000 boot_v1.7.bin 0x01000 at/512+512/user1.1024.new.2.bin 0xfc000 esp_init_data_default.bin 0x7E000 blank.bin 0xFE000 blank.bin

    esptool.py v3.0
    Serial port /dev/ttyUSB0
    Connecting....
    Detecting chip type... ESP8266
    Chip is ESP8266EX
    Features: WiFi
    Crystal is 26MHz
    MAC: e8:db:84:dc:4e:77
    Uploading stub...
    Running stub...
    Stub running...
    Configuring flash size...
    Compressed 4080 bytes to 2936...
    Wrote 4080 bytes (2936 compressed) at 0x00000000 in 0.4 seconds (effective 78.3 kbit/s)...
    Hash of data verified.
    Compressed 427044 bytes to 305765...
    Wrote 427044 bytes (305765 compressed) at 0x00001000 in 41.6 seconds (effective 82.1 kbit/s)...
    Hash of data verified.
    Compressed 128 bytes to 75...
    Wrote 128 bytes (75 compressed) at 0x000fc000 in 0.0 seconds (effective 32.0 kbit/s)...
    Hash of data verified.
    Compressed 4096 bytes to 26...
    Wrote 4096 bytes (26 compressed) at 0x0007e000 in 0.0 seconds (effective 2153.5 kbit/s)...
    Hash of data verified.
    Compressed 4096 bytes to 26...
    Wrote 4096 bytes (26 compressed) at 0x000fe000 in 0.0 seconds (effective 2133.6 kbit/s)...
    Hash of data verified.

    Leaving...
    Hard resetting via RTS pin...

Firmware check in serial monitor  
>AT+GMR

    AT version:1.5.0.0(Oct 24 2017 12:03:18)
    SDK version:2.1.0(ace2d95)
    compile time:Oct 24 2017 15:48:02
    Bin version(Wroom 02):1.5.1
    OK

### After upload

Remove the ground connection on GPIO0 and boot up and connect again  
>$ picocom -b 115200 /dev/ttyUSB0 --omap crcrlf  

## AT commands

Check firmware version  
>AT+GMR  

    AT version:1.3.0.0(Jul 14 2016 18:54:01)
    SDK version:2.0.0(5a875ba)
    v1.0.0.3
    Mar 13 2018 09:35:47
    OK

Check WiFi mode  
>AT+CWMODE?  

    +CWMODE:0

    OK

Set as station  
>AT+CWMODE=1

    OK

Mode 1 -> STA (station)  
Mode 2 -> AP (access point)  
Mode 3 -> Both

Search for access points  
>AT+CWLAP

    +CWLAP:(0,"ESP-E0569F",-56,"52:02:91:e0:56:9f",11)
    +CWLAP:(2,"tureborg2",-55,"00:1b:2f:50:e6:16",11)

    OK

Connect to access point  
>AT+CWJAP="\<access point>","\<password>"  

    WIFI CONNECTED
    WIFI GOT IP

    OK

Show IP-address
>AT+CIFSR

    +CIFSR:APIP,"192.168.4.1"
    +CIFSR:APMAC,"ea:db:84:dc:4e:77"
    +CIFSR:STAIP,"192.168.10.78"
    +CIFSR:STAMAC,"e8:db:84:dc:4e:77"

    OK

Disconnect from access point
>AT+CWQAP

    WIFI DISCONNECT

    OK

Set serial speed  
>AT+CIOBAUD=9600

    OK

Permanently set serial speed, for example, 9600 baud / 8 data bits / 1 stop bits and none parity and flow control  
>AT+UART_DEF=9600,8,1,0,0

Reset  
>AT+RST

    OK
    WIFI DISCONNECT
    ...
    Ai-Thinker Technology Co. Ltd.

    invalid
    WIFI CONNECTED
    WIFI GOT IP

## esptool.py

When using esptool you must pull GPIO0 to GND  

Allowed baud rates:  
74880, 115200, 230400, 460800, 921600, 1500000, >1500000

Read MAC address  
>$ esptool.py -p /dev/ttyUSB0 read_mac

    esptool.py v3.0
    Serial port /dev/ttyUSB0
    Connecting....
    Detecting chip type... ESP8266
    Chip is ESP8266EX
    Features: WiFi
    Crystal is 26MHz
    MAC: e8:db:84:dc:4e:77
    Uploading stub...
    Running stub...
    Stub running...
    MAC: e8:db:84:dc:4e:77
    Hard resetting via RTS pin...

Find flash size  
>$ esptool.py -p /dev/ttyUSB0 flash_id

    esptool.py v3.0
    Serial port /dev/ttyUSB0
    Connecting....
    Detecting chip type... ESP8266
    Chip is ESP8266EX
    Features: WiFi
    Crystal is 26MHz
    MAC: e8:db:84:dc:4e:77
    Uploading stub...
    Running stub...
    Stub running...
    Manufacturer: 20
    Device: 4014
    Detected flash size: 1MB
    Hard resetting via RTS pin...

Erase flash  
>$ esptool.py -p /dev/ttyUSB0 erase_flash

    esptool.py v3.0
    Serial port /dev/ttyUSB0
    Connecting....
    Detecting chip type... ESP8266
    Chip is ESP8266EX
    Features: WiFi
    Crystal is 26MHz
    MAC: e8:db:84:dc:4e:77
    Uploading stub...
    Running stub...
    Stub running...
    Erasing flash (this may take a while)...
    Chip erase completed successfully in 4.1s
    Hard resetting via RTS pin...

Create a merged .bin  
>$ esptool.py --chip esp8266 merge_bin -o merged-flash.bin --flash_mode dio --flash_size 1MB 0x00000 boot_v1.7.bin 0x01000 at/512+512/user1.1024.new.2.bin 0xFC000 esp_init_data_default_v08.bin 0x7E000 blank.bin 0xFE000 blank.bin

Upload merged .bin  
>$ esptool.py -p /dev/ttyUSB0 -b 115000 write_flash 0x0 merged-flash.bin

Verify upload
>$ esptool.py -p /dev/ttyUSB0 -b 74880 verify_flash --diff yes 0x00000 boot_v1.7.bin 0x01000 at/512+512/user1.1024.new.2.bin 0xfc000 esp_init_data_default_v08.bin 0x7e000 blank.bin 0xfe000 blank.bin

## picocom

Allowed baud rates:  
300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200  

Connect
>$ picocom -b 115200 /dev/ttyUSB0 --omap crcrlf  

View help  
> [Ctrl+a][Ctrl+h]  

Quit  
> [Ctrl+a][Ctrl+q]  

## Links

Espressif AT firmware:  
[https://www.espressif.com/en/support/download/at](https://www.espressif.com/en/support/download/at)  

AT instruction set  
[https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf](https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf)  

[https://docs.linuxconsulting.mn.it/esp8266/firmware-programming](https://docs.linuxconsulting.mn.it/esp8266/firmware-programming)  
[https://www.espressif.com/en/products/socs/esp8266ex/resources](https://www.espressif.com/en/products/socs/esp8266ex/resources)  
