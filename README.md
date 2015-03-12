# README #

Battle of the Rockets - Rover Competition 2015

## Download Latest Release ##
On bitbucket, click the cloud button with the down arrow (Downloads) for this project.  Find the latest Zip folder, this is the latest release for this project

### About this Repository ###

This is the repository containing all of the rover electrical schematics, PCB designs  and arduino source code.  

### Applications Used ###
* Electrical Cad - KiCad (for schematics, PCB design and BOM generation)
* Arduino - Arduino 1.6.1 

### How do I get set up? ###

* To edit code, download Arduino - [Arduino Download](http://arduino.cc/en/Main/Software)
* To view or contribute to the electrical schematic, download KiCad.  [KiCad Download](http://kicad.nosoftware.cz/).  For Window, use the latest file (I used KiCad_testing-2015.01.17-BZR5376_Win_full_version.exe)

### How do I open KiCad Files? ###

* Open KiCad, then click File -> Open Project.  Open rover.pro (located under Rover 2015/electrical).  

* To view the schematic, click the button at the top left of the larger "main" panel in the main window, titled Eeschema - Electronics Schematic Editor. 

* To view the PCB design, click the 3rd button over titled Pcbnew - Printed Circuit Board Editor.

### How do I open Arduino Files? ###

* The pololu QTR Sensors library is needed for the reflectance sensor.  Download and follow the instructions here - [QTR Sensors Library](https://www.pololu.com/docs/0J19/all#2).  Find the Download Zip button on the github page (right hand side, lower part of the page).  Extract the zip file, and drag the QTRSensors subfolder into the arduino installation directory/libraries.
* Open the Arduino application and open the rover project to edit, compile and upload the source code
* The arduino code is located under Rover 2015/arduino/src