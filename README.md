# Generic Torquer – NOS3 Component
This repository contains the NOS3 Generic Torquer Component. This includes flight software (fsw), ground software (gsw), and simulation (sim) directories.

## Overview
Torquers, or magnetorquers, are commonly used on spacecraft as a secondary attitude control mechanism. They consist of electromagnets placed asymmetrically. Different currents running through them then generate different magnetic fields, and the torque created by the interaction of the spacecraft magnetic field and the Earth’s magnetic field rotates the vehicle. Because of the small amounts of torque available, magnetorquers are only infrequently used as the primary attitude control mechanism; they frequently serve as a secondary mechanism, though, and are used to provide small rotational changes or to gradually unload reaction wheels. 
The generic torquer is a device which accepts as input a current (as a percent of the maximum) and returns a value of the generated magnetic field. 
The available flight software is for use in the core Flight System (cFS) while the ground software supports COSMOS.
A NOS3 simulation is available which uses a 42 data provider.

## Technical Specifications
- Maximum magnetic field strength __

## Mechanical
### Reference System
The +z axis is down the length of the magnetorquer (in the same direction as the coil). The +x and +y axes are perpendicular to the coil, and together with the +z axis make an orthogonal, right-handed coordinate system.

## Communications
The NOS3 Generic Torquer Component can communicate via the SPI protocol.

### Data Format
The data structure for communications is explained below:
- Character transmission (unsigned char):  (Byte_0(LSB)) --> to communications channel
- Floating data transmission (float):  Float codification according to IEEE 754-1985 standard for single-precision floating 32 bits:  (sign|exponent|fraction) = (Byte_3(MSB)|Byte_2|Byte_1|Byte_0(LSB)) --> to communications channel
    - Floating value = s x 2^e x m, where:
        - Sign(s): 1 bit (0 = positive, 1 = negative)
        - Exponent: 8 bits (e = Exponent - 127)
        - Fraction: 23 bits (m = 1.Fraction)

### Frame Format
This protocol uses one message:
- Command message: from master to slave

The master is the onboard computer of the satellite, or the master of the communication bus, and the slave is the generic torquer. The command message directs a certain amount of power to the magnetorquer, which is measured as a percentage of the maximum possible power.

The commands sent to the sensor shall comply with the format below:
- Sync Word = 0xDEADBEEF (4 bytes) - Synchronization word that indicates the start of a new frame.
- Command Code = 0xXX (1 byte) - Corresponds to the code of the incoming command. Since there is only one command, this command will be 0x01.
- Length = 0x02 (1 byte) - For commands it is fixed to 0x02.
- Application Data = 0xXX (1 byte) – what the desired percent power is, in hexadecimal. Setting the magnetorquer to 100% power, for instance, would be done with 0x64 (as 64 in hexadecimal is equal to 100 in decimal)
- Checksum = 0xXX (1 byte) - For command 0x01 and a percent value of 0x00, the value of the checksum field is 0x02. It is calculated by 
    - E.g. The message commands 100% power to the magnetorquer.
        - DE AD BE EF 01 02 64 
        - 01 + 02 + 64 = 0x67.  Least significant byte of 0x67 is 0x67.
        - So checksum is 0x67


Every response sent to the master shall comply with the format described below:
- Sync Word = 0xDEADBEEF (4 bytes) - Synchronization word that indicates the start of a new frame.
- Command Code = 0xXX (1 byte) - Corresponds to the code of the command to which this response refers. Since there is only a single command, this will be 0x01.
- Length = 0xXX (1 byte) - The sum of the number of bytes of the fields "Application Data" and "Checksum", or 0x02.
- Application Data = 0xXX (1 byte) – Corresponds to the error message passed back; 0x00 means no error, while 0x01 means the magnetorquer was not set correctly or something of that sort.
- Checksum = 0xXX (1 byte) - Used to check the integrity of the packet.  It is calculated by adding all bytes in "Command Code", "Length", and "Application Data" fields and extracting the least significant byte of the result.
    - E.g. The torquer successfully received and acted upon a message
        - DE AD BE EF 01 02 00 
        - 01 + 02 + 00 = 0x03.  Least significant byte of 0x03 is 0x03.
        - So checksum is 0x03

### SPI Protocol Format
The following describes an example of a command/response communication for command code 0x01 via SPI.  Note that the IDLE byte value is 0xFF:

- SPI Command:
    - On board computer to generic fine sun sensor device:
        - Sync Word = 0xDEADBEEF (4 bytes)
        - Command Code - 0x01 (1 byte)
        - Length = 0x02 (1 byte)
        - Application Data:
            - Percent power = 0xXX (1 byte)
        - Checksum = 0xXX (1 byte)

### Commands
The command code implemented is:
- Command Code = 0x01, Name = percent power, Functionality = Command the magnetorquers to be set to a percentage of their maximum power.

#### Command 0x01:  Percent power
Command for the torquers to be set to a percentage of their maximum power.  
- Command
    - Sync Word = 0xDEADBEEF (4 bytes)
    - Command Code = 0x01 (1 byte)
    - Length = 0x02 (1 byte)
    - Application Data:
	- Percent power = 0xXX (1 byte)
    - Checksum = 0xXX (1 byte)

- Response
    - Sync Word = 0xDEADBEEF (4 bytes)
    - Command Code = 0x01 (1 byte)
    - Length = 0x02 (1 byte)
    - Application Data:
        - Error code = 0xXX (1 byte)
    - Checksum = 0xXX (1 byte)

Error codes:
- 0 = No error.  The torquer is set to the given power.
- 1 = Error.  The magnetorquer was not able to be set to the given power value for some reason.

