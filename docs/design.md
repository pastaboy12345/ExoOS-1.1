# ExoOS 1.1 EcoSys Design

ExoOS 1.1 is a clean reboot of ExoOS.

It does not use design inspiration from the old C# ExoOS prototype.

## Identity

- OS name: ExoOS
- Version: 1.1
- Core/kernel: EcoSys
- Boot menu: ExoBoot
- Shell/prompt: ExoPrompt
- Native root volume: E:/
- Design style: UNIX/DOS hybrid

## Core rules

1. E:/ is the native system root.
2. / paths are compatibility aliases for E:/.
3. The system boots through a graphical-ish boot menu.
4. The boot menu shows a splash screen before the prompt.
5. The first target is a stable prompt-based OS.
6. The old C# ExoOS prototype is not a design source.

## Native path examples

E:/System
E:/Programs
E:/Users
E:/Devices
E:/Config
E:/Temp
E:/Logs

## Compatibility path examples

/System
/Programs
/Users
/Devices

These resolve internally to E:/ paths.
