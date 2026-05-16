#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "../include/ecosys.h"

__attribute__((used, section(".limine_requests")))
static volatile uint64_t limine_base_revision[3] = {
    0xf9562b2d5c95a6c8,
    0x6a7b384944536bdc,
    3
};

struct limine_framebuffer {
    void *address;
    uint64_t width;
    uint64_t height;
    uint64_t pitch;
    uint16_t bpp;
    uint8_t memory_model;
    uint8_t red_mask_size;
    uint8_t red_mask_shift;
    uint8_t green_mask_size;
    uint8_t green_mask_shift;
    uint8_t blue_mask_size;
    uint8_t blue_mask_shift;
    uint8_t unused[7];
};

struct limine_framebuffer_response {
    uint64_t revision;
    uint64_t framebuffer_count;
    struct limine_framebuffer **framebuffers;
};

struct limine_framebuffer_request {
    uint64_t id[4];
    uint64_t revision;
    struct limine_framebuffer_response *response;
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = {
        0x9d5827dcd881dd75,
        0xa3148604f6fab11b,
        0x2b8f1b4fd3bbeb75,
        0x18f780650a4d9d5c
    },
    .revision = 0,
    .response = 0
};

__attribute__((used, section(".limine_requests_start")))
static volatile uint64_t limine_requests_start_marker[4] = {
    0xf6b8f4b39de7d1ae,
    0xfab91a6940fcb9cf,
    0x785c6ed015d3e316,
    0x181e920a7852b9d9
};

__attribute__((used, section(".limine_requests_end")))
static volatile uint64_t limine_requests_end_marker[2] = {
    0xadc0e0531bb10d03,
    0x9572709f31764c62
};

static struct limine_framebuffer *fb = NULL;

static void halt_forever(void) {
    for (;;) {
        __asm__ volatile ("hlt");
    }
}

static void delay(volatile uint64_t count) {
    while (count--) {
        __asm__ volatile ("pause");
    }
}

static void put_pixel(uint64_t x, uint64_t y, uint32_t color) {
    if (!fb || x >= fb->width || y >= fb->height) {
        return;
    }

    uint32_t *pixel = (uint32_t *)((uint8_t *)fb->address + y * fb->pitch + x * 4);
    *pixel = color;
}

static void fill_rect(uint64_t x, uint64_t y, uint64_t w, uint64_t h, uint32_t color) {
    for (uint64_t yy = y; yy < y + h; yy++) {
        for (uint64_t xx = x; xx < x + w; xx++) {
            put_pixel(xx, yy, color);
        }
    }
}

static void draw_border(uint64_t x, uint64_t y, uint64_t w, uint64_t h, uint32_t color) {
    fill_rect(x, y, w, 2, color);
    fill_rect(x, y + h - 2, w, 2, color);
    fill_rect(x, y, 2, h, color);
    fill_rect(x + w - 2, y, 2, h, color);
}

static void draw_logo(uint64_t cx, uint64_t cy) {
    for (uint64_t i = 0; i < 60; i++) {
        put_pixel(cx + i, cy - i, 0x9fa8ff);
        put_pixel(cx - i, cy - i, 0x9fa8ff);
        put_pixel(cx + i, cy + i, 0x9fa8ff);
        put_pixel(cx - i, cy + i, 0x9fa8ff);
    }

    fill_rect(cx - 24, cy - 8, 48, 16, 0xdfe3ff);
}

static void draw_boot_menu(void) {
    fill_rect(0, 0, fb->width, fb->height, 0x101018);

    uint64_t box_w = 560;
    uint64_t box_h = 340;
    uint64_t box_x = (fb->width - box_w) / 2;
    uint64_t box_y = (fb->height - box_h) / 2;

    fill_rect(box_x, box_y, box_w, box_h, 0x202030);
    draw_border(box_x, box_y, box_w, box_h, 0x8080d0);
    fill_rect(box_x + 8, box_y + 8, box_w - 16, box_h - 16, 0x181824);

    draw_logo(box_x + box_w / 2, box_y + 72);

    fill_rect(box_x + 180, box_y + 116, 200, 10, 0xe8e8ff);
    fill_rect(box_x + 215, box_y + 134, 130, 8, 0xa8b0ff);

    fill_rect(box_x + 70, box_y + 180, box_w - 140, 36, 0x4050a0);
    fill_rect(box_x + 90, box_y + 193, 120, 8, 0xffffff);

    fill_rect(box_x + 70, box_y + 226, box_w - 140, 30, 0x282838);
    fill_rect(box_x + 90, box_y + 237, 170, 7, 0xb8b8d8);

    fill_rect(box_x + 70, box_y + 264, box_w - 140, 30, 0x282838);
    fill_rect(box_x + 90, box_y + 275, 95, 7, 0xb8b8d8);

    fill_rect(box_x + 120, box_y + 310, 120, 6, 0x8080d0);
    fill_rect(box_x + 320, box_y + 310, 120, 6, 0x8080d0);
}

static void draw_splash(void) {
    fill_rect(0, 0, fb->width, fb->height, 0x050510);

    uint64_t cx = fb->width / 2;
    uint64_t cy = fb->height / 2;

    draw_logo(cx, cy - 80);

    fill_rect(cx - 140, cy + 10, 280, 18, 0xe8e8ff);
    fill_rect(cx - 100, cy + 42, 200, 10, 0x9098ff);

    fill_rect(cx - 180, cy + 100, 360, 18, 0x202030);
    draw_border(cx - 180, cy + 100, 360, 18, 0x6060d0);
    fill_rect(cx - 176, cy + 104, 250, 10, 0x7070ff);
}

static void draw_prompt_screen(void) {
    fill_rect(0, 0, fb->width, fb->height, 0x000000);

    fill_rect(32, 32, 220, 12, 0xffffff);
    fill_rect(32, 60, 70, 10, 0x80ff80);
    fill_rect(108, 60, 12, 10, 0x80ff80);
    fill_rect(126, 60, 22, 10, 0x80ff80);
}

void kmain(void) {
    if (framebuffer_request.response == NULL ||
        framebuffer_request.response->framebuffer_count < 1) {
        halt_forever();
    }

    fb = framebuffer_request.response->framebuffers[0];

    draw_boot_menu();
    delay(220000000);

    draw_splash();
    delay(220000000);

    draw_prompt_screen();

    halt_forever();
}
