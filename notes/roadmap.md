# ExoOS 1.1 EcoSys Roadmap

## Alpha 0.1

Goal: prove the new OS line boots.

- [ ] Boot in QEMU
- [ ] Show framebuffer text
- [ ] Show GUI-ish boot menu
- [ ] Accept keyboard selection
- [ ] Show splash screen
- [ ] Enter E:/> prompt
- [ ] Implement help
- [ ] Implement clear
- [ ] Implement echo
- [ ] Implement about
- [ ] Implement sys
- [ ] Implement reboot

## Alpha 0.2

Goal: make the prompt feel like ExoOS.

- [ ] Add ExoPath parser
- [ ] Add current working directory
- [ ] Add cd
- [ ] Add pwd
- [ ] Add ls/dir
- [ ] Add fake in-memory E:/ tree

## Alpha 0.3

Goal: start becoming a real OS.

- [ ] Add interrupt handling
- [ ] Add timer
- [ ] Add keyboard driver
- [ ] Add memory map support
- [ ] Add panic screen
- [ ] Add serial logging

## Rules

- Do not copy the old C# prototype design.
- Keep E:/ as the native root.
- Keep the first version prompt-based.
- GUI boot menu first, full GUI later.
