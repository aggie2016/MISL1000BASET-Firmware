# MISL1000BASET-Firmware
Command-Line interface and Web Server for the MISL 1000BASE-T Switching Layer. A collaboration between Eagle Embedded Engineering, Texas A&amp;M University, and the National Aeronautics and Space Administration


## Work In Progress
Please check back for further updates as they are committed.


### Building Under Linux with CMAKE
This project was built with the intention of removing any unnecessary dependencies on third party paid packages. However, if a developer wishes to use a particular IDE to further develop this project, CMAKE can generate the necessary project files for most IDEs.

In order to build this project using just a G++ compiler and CMAKE, the following packages must be installed.
Please note that all of the below items were downloaded for Ubuntu 17.10:
- apt-get install build-essential software-properties-common -y
- apt-get install gcc-snapshot -y
- apt-get install gcc-4.8 g++-4.8 -y
- apt-get install cmake
- apt-get install libusb-1.0.0-dev
- apt-get install pkg-config
- apt-get install libtool
- apt-get install automake

Optionally:
- apt-get install git


Additionally, the following dependencies are required to build this project for ARM targets:
- GCC ARM EABI Cross Compiler
    https://launchpad.net/gcc-arm-embedded/4.7/4.7-2013-q1-update/+download/gcc-arm-none-eabi-4_7-2013q1-20130313-linux.tar.bz2
- TivaWare C Series v2.1.4.178
http://software-dl.ti.com/tiva-c/SW-TM4C/latest/index_FDS.html
- LM4Flash Tool
```cpp
   [chris@linux-mainframe]$ git clone https://github.com/utzig/lm4tools.git
```
- OpenOCD Debugger (w/ ICDI support)
```cpp
[chris@linux-mainframe ARM]$ git clone git://git.code.sf.net/p/openocd/code openocd.git
[chris@linux-mainframe ARM]$ cd openocd.git
[chris@linux-mainframe openocd.git]$ ./bootstrap
[chris@linux-mainframe openocd.git]$ ./configure --prefix=/usr --enable-maintainer-mode --enable-stlink --enable-ti-icdi
[chris@linux-mainframe openocd.git]$ make
[chris@linux-mainframe openocd.git]$ sudo make install
```

The TivaC static libraries required for compilation are included under the "externals" folder.

Once everything is installed, you project directory should look like the following
```
---- HOME FOLDER
    |-> tools
          |-> lm4flash
          |-> openOCD
    |-> MISL1000BaseT-Firmware
          |-> build
          
```    

To finally build the project, navigate to the "build" folder under MISL1000BaseT-Firmware. If one does not exist, use:
```
[chris@linux-mainframe MISL1000BaseT-Firmware]$ mkdir build 
[chris@linux-mainframe MISL1000BaseT-Firmware]$ cd build 
``` 

Run cmake and then make -j to build the .axf output file.
```
[chris@linux-mainframe build]$ cmake ..
[chris@linux-mainframe build]$ make -j 
```

To flash the file, ensure you have sudoer permissions, the TI ICDI debug board is connected over both USB to the computer and JTAG to the target, and then run the following
```
[chris@linux-mainframe build]$ sudo make flash
```