# BSODScreen

[![Visitors](https://api.visitorbadge.io/api/visitors?path=https%3A%2F%2Fgithub.com%2Fhfiref0x%2FBSODScreen&countColor=%23263759&style=flat)](https://visitorbadge.io/status?path=https%3A%2F%2Fgithub.com%2Fhfiref0x%2FBSODScreen)

## ReactOS Screensaver

---

## System Requirements

- Windows 7/8/8.1/10/11 (x86-32/x64)
- OpenGL hardware rendering support (optional)
- ReactOS x86-32 0.4.15 or newer

---

## Warning (ReactOS Only)

This program may crash ReactOS or impact its stability, potentially resulting in data loss or application failure. Use at your own risk.

The screensaver exploits a critical system bug, randomly chosen from hundreds present in ReactOS. This bug may be fixed or behave differently in future ReactOS versions.

By default, the BSOD feature is disabled. To enable it: open the screensaver configuration dialog, select the screensaver, right-click it, and choose "Configure".

---

## Building from Source

BSODScreen is written in C/C++ and includes complete source code.  
To build from source, you need Microsoft Visual Studio 2019 or newer.

### Build Instructions

- Set the Platform Toolset for the project you wish to build (Project → Properties → General):
  - Use `v141` for Visual Studio 2019/2022
- Minimum required Windows SDK version: 8.1

---

## Third-party Components

This project uses the Khronos OpenGL / OpenGL ES XML API Registry.  
See `KHRGL/wglext.h` and `KHRGL/glext.h` for details.

---

## Authors

- Screensaver © 2018–2025 BSODScreen Project
- 3D Scene © 2018 Uldis Rinkevichs
