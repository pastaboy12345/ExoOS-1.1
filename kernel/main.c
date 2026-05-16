void kernel_main(void) {
    volatile char *video = (volatile char *)0xB8000;

    video[0] = 'O';
    video[1] = 0x0F;
    video[2] = 'S';
    video[3] = 0x0F;
}
