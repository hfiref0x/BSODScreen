
# BSODScreen
## ReactOS Screensaver

# System Requirements

+ x86-32/x64 Windows 7/8/8.1/10;
+ OpenGL hardware rendering support (optional);
+ ReactOS x86-32 0.4.10 and later versions.

# Warning (apply only for ReactOS)

This program may crash ReactOS, affect it stability, which may result in data lost or program crash itself. You use it at your own risk.

This Screensaver utilize critical system bug which was taken randomly from one of few hundreds(!) available in ReactOS. It maybe fixed or not working in future versions of ReactOS.

By default this BSOD is turned off. You can turn it on using screensaver configuration dialog -> select screensaver, right click on it -> select "Configure".

# Build

BSODScreen comes with full source code written in C/C++.
In order to build from source you need Microsoft Visual Studio 2015 and later versions.

## Instructions

* Select Platform ToolSet first for project in solution you want to build (Project->Properties->General): 
  * v120 for Visual Studio 2013;
  * v140 for Visual Studio 2015; 
  * v141 for Visual Studio 2017.
* For v140 and above set Target Platform Version (Project->Properties->General):
  * If v140 then select 8.1 (Note that Windows 8.1 SDK must be installed);
  * If v141 then select 10.0.17763.0 (Note that Windows 10.0.17763 SDK must be installed). 

# 3rd party components usage

This project uses Khronos OpenGL / OpenGL ES XML API Registry. See KHRGL\wglext.h, KHRGL\glext.h for more info.

# Authors

+ Screensaver (c) 2018 BSODScreen Project
+ 3D Scene (c) 2018 by Uldis Rinkevichs
