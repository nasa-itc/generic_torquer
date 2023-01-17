
# Generic_torquer - NOS3 cFS Application

This repository contains the NOS3 Generic_torquer cFS application.

## Overview

Torquers, or magnetorquers, are commonly used on spacecraft as a secondary attitude 
control mechanism. They consist of electromagnets placed asymmetrically. Different 
currents running through them then generate different magnetic fields, and the 
torque created by the interaction of the spacecraft magnetic field and the Earth’s 
magnetic field rotates the vehicle. Because of the small amounts of torque 
available, magnetorquers are only infrequently used as the primary attitude control 
mechanism; they frequently serve as a secondary mechanism, though, and are used to 
provide small rotational changes or to gradually unload reaction wheels. 


## Documentation
Currently support exists for the following versions:
* [cFS 6.7/6.8](https://cfs.gsfc.nasa.gov/)

# Commanding
Refer to the file `fsw/platform_inc/generic_torquer_app_msgids.h` for the Generic_torquer app message IDs
Refer to the file `fsw/src/generic_torquer_app_msg.h` for the Generic_torquer app command codes

The generic_torquer is relatively simple in outline; it takes as input only a value
for the current (in amperes) and returns a value for the magnetic field generated.
The equation used to calculate the dipole is m=nIA, where n and A are constants for a
given magnetorquer. I, the current, is an input, and m (the magnetic dipole) is the 
output.

*it is possible that we will need to provide more calculation/return values than just
a magnetic field; if so, there might need to be additional facts about the location or
arrangement of the magnetorquers and such.

## Versioning
We use [SemVer](http://semver.org/) for versioning. For the versions available, see the tags on this repository.
