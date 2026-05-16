# ExoPath

ExoPath is the native path system for ExoOS 1.1.

## Native root

The native root volume is:

E:/

Unlike DOS/Windows, E:/ is not just an arbitrary drive letter. It is the official ExoOS system volume.

## Normalization

These paths should resolve to the same internal location:

E:/System/Kernel
/System/Kernel

Internal normalized representation:

volume = E
path = /System/Kernel

## Standard directories

E:/System
E:/Programs
E:/Users
E:/Devices
E:/Config
E:/Temp
E:/Logs
E:/Mounts

## Command prompt behavior

At root:

E:/>

Inside System:

E:/System>

Inside user directory:

E:/Users/William>
