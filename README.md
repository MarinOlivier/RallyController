# DMD2 Compatible Bluetooth Rally Roadbook Controller


This repo is a fork of Thomas Styles's repo : https://github.com/StylesRallyIndustries/RallyController

The goal of this project is to develop an OpenSource Rally controller compatible with DMD2 app (https://www.drivemodedashboard.com/). 


## Hardware

I do not change anything in hardware (for the moment), so you can use the original instructions and STL files.

Complete Instructions:
https://www.instructables.com/Bluetooth-Navigation-Digital-Roadbook-Controller-4/

STL Files:
https://www.thingiverse.com/stylesrallyindustries/designs

## Software

![DMD2 button demo](https://github.com/MarinOlivier/RallyController/blob/main/doc/src/DMD2_RallyCtrlDemo.gif)

The soft has been (almost completely) re-writen to match my needs :
* Button 1
  * quick press -> one-step zoom in
  * hold -> multiple step zoom in 
* Button 2
  * quick press -> one-step zoom out
  * hold -> multiple step zoom out
* Button 3
  * quick press -> toggle follow mode
  * hold -> change online layer
* Button 4
  * quick press -> toggle touch (lock / unlock screen)
  * hold -> toggle night / day mode

In fact, the software only send commands to DMD2 and you need to configure in DMD2 each behaviours like this :

![DMD2 Remote configuration 1](https://github.com/MarinOlivier/RallyController/blob/main/doc/src/dmd2_remotectrl_settings_1.png)

![DMD2 Remote configuration 2](https://github.com/MarinOlivier/RallyController/blob/main/doc/src/dmd2_remotectrl_settings_2.png)

