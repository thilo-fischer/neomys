Directory includes the schematics and PCB design used to build hardware of Okey adaptations.

The EDA software used is KiCad, http://kicad-pcb.org/. As Okey, KiCad is open source such that anybody can use the software free of charge. (There are some free versions of commercial EDA software available, but those have special restrictions which makes them inapplicable for most Okey PCBs, e.g. PCB sizes below 80 x 100 mm.)

Most schematics and PCB files use parts not (yet) available from the standard libraries that come with KiCad. These parts are taken from 3rd party library files that can be found in the internet. Due to unclear license and copyright constraints of those 3rd party library, these library files are not included in the Okey repository. Currently, these parts listed below are taken from the referenced libraries:

Cherry MX switches
  http://www.key64.org/downloads/key64-20120707.tgz => cherry.lib

7-stage binary counter 4024
  http://www.kicadlib.org/modules/gajda_cmosieee.lib.zip

8 bit SIPO shift latch register 4094N
  https://github.com/musa/kicad-library/blob/master/library/40xx.lib



Todo-List

- Constoller board: Change BCE Transistors to more common CBE Transistors
- Extra buttons board: Adapt button footprint to match 2.54 mm raster *and* 4.50/6.50 mm (6 mm) buttons (e.g. JTP-1130)

Notes

Grid used to place Cherry MX switches and route tracks: 18.5mm x 18.5mm, 1.85mm x 1.85mm
