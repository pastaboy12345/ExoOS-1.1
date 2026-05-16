# ExoOS 1.1 Boot Flow

The intended boot flow is:

Firmware
  ↓
ExoBoot
  ↓
GUI-ish boot menu
  ↓
Splash screen
  ↓
EcoSys kernel initialization
  ↓
Mount E:/
  ↓
Start ExoPrompt
  ↓
E:/>

## Boot menu

The boot menu should use framebuffer graphics, not a full desktop GUI.

Initial menu:

┌──────────────────────────────────────────────┐
│                  ◇ ExoOS                     │
│              1.1 EcoSys Edition              │
│                                              │
│          > Start ExoOS                       │
│            Recovery Prompt                   │
│            Boot Log                          │
│            Reboot                            │
│                                              │
│     E:/ native system     UNIX/DOS hybrid    │
└──────────────────────────────────────────────┘

## Splash screen

◇ ExoOS
EcoSys is starting...

Mounting E:/...
Starting ExoPrompt...

## Prompt

ExoOS 1.1 EcoSys

E:/>
