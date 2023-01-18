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
The NOS3 Generic Torquer communicates by means of the hardware library (hwlib) defined in https://github.com/nasa-itc/hwlib/tree/dev. Specifically, it makes use of two functions from the torquer library at https://github.com/nasa-itc/hwlib/blob/dev/fsw/public_inc/libtrq.h to send commands to the torquers.


### Commands
There are two commands defined in libtrq which this generic torquer uses. They are:
- trq_set_direction(trq_info_t* device, bool direction)
- trq_command(trq_info_t *device, uint8_t percent_high, bool pos_dir)


#### Command trq_set_direction
Command for the current to the torquers to be set in one direction or the other.
- Command
    - trq_info_t* device = the address of the device being controlled
    - bool direction = the direction the current takes through the torquer

- Response
    - int32_t response = an integer which indicates the success or failure of the command

#### Command trq_command
Command for a torquer to be set to a percentage of its maximum power.  
- Command
    - trq_info_t* device = the address of the device being controlled
    - uint8_t percent_high = percent power to send through the torquer
    - bool direction = the direction the current should take

- Response
    - int32_t response = an integer which indicates the success or failure of the command

Error codes:
- 0 = No error.  The torquer is set to the given power.
- 1 = Error.  The magnetorquer was not able to be set to the given power value for some reason.


