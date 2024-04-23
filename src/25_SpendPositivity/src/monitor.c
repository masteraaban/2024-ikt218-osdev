#include <../include/monitor.h>
#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "libc/stdarg.h"
#include <libc/string.h>

// Constants for screen dimensions and video memory address
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define VIDEO_ADDRESS 0xB8000

// Pointer to video memory for text display
static u16int *video_memory = (u16int *)VIDEO_ADDRESS;
// Cursor position variables
static u8int cursor_x = 0;
static u8int cursor_y = 0;

// Move the hardware cursor to the current x, y position
static void move_cursor() {
    u16int cursorLocation = cursor_y * SCREEN_WIDTH + cursor_x;
    outb(0x3D4, 14);
    outb(0x3D5, cursorLocation >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursorLocation);
}

// Scroll the screen if needed
static void scroll() {
    u8int attributeByte = (0 << 4) | (15 & 0x0F);
    u16int blank = 0x20 | (attributeByte << 8);

    if (cursor_y >= SCREEN_HEIGHT) {
        for (int i = 0; i < (SCREEN_HEIGHT - 1) * SCREEN_WIDTH; i++) {
            video_memory[i] = video_memory[i + SCREEN_WIDTH];
        }
        for (int i = (SCREEN_HEIGHT - 1) * SCREEN_WIDTH; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++) {
            video_memory[i] = blank;
        }
        cursor_y = SCREEN_HEIGHT - 1;
    }
}

// Display a character at the current cursor position
void monitor_put(char c) {
    u8int backColour = 0;
    u8int foreColour = 15;
    u8int attributeByte = (backColour << 4) | (foreColour & 0x0F);
    u16int attribute = attributeByte << 8;
    u16int *location;

    if (c == 0x08 && cursor_x) {
        cursor_x--;
    } else if (c == 0x09) {
        cursor_x = (cursor_x + 8) & ~(8 - 1);
    } else if (c == '\r') {
        cursor_x = 0;
    } else if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c >= ' ') {
        location = video_memory + (cursor_y * SCREEN_WIDTH + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }
    if (cursor_x >= SCREEN_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    scroll();
    move_cursor();
}

// Clear the screen
void monitor_clear() {
    u8int attributeByte = (0 << 4) | (15 & 0x0F);
    u16int blank = 0x20 | (attributeByte << 8);
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video_memory[i] = blank;
    }
    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

// Write a string to the screen
void monitor_write(char *c) {
    int i = 0;
    while (c[i]) {
        monitor_put(c[i++]);
    }
}
