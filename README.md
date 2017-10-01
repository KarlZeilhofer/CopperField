# CopperField
![Image](./CopperField.png)

## Purpose
This software is used, to generate G-Code out of Gerber Files. 
Gerber is the default exchange format for manufacturing of printed circuit boards (PCBs). 
The G-Code is used to drive a CNC-milling machine to isolate the copper tracks. 

## Shortcuts
  * **G** G-Code settings
  * **L** Layer settings
  * **Space** Set relative coordinate origin
  * **M** Calculate milling paths
  * **Home** Zoom to whole drawing


## Still in Pre-Alpha-State
Some Demos are working, but there are still many features missing. 

### Whats already implemented
* Load and display Gerber files for bottom and top layer
* Load and display drill files
* Isolate simple geometries (connected pads and tracks)
* export proper G-code
* option for mirroring before exporting

### Whats really missing
* Usable option for engraved/isolated/ignored
* Polygon support
* Improved element fusion to logical nets
* Further many TODOs, please have a look into the source code
* Proper outline milling

If you have interest on this code, please contact me: karl@zeilhofer.co.at

## Screenshots
please have a look into the screenshots folder
