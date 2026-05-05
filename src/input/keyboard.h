#pragma once

#include "graphics/font.h"

#include <stdint.h>

void keyboard_start_capture(
  uint8_t* text, int max_length, int allow_punctuation, int box_width, e_font font, int multiline = 0);
void keyboard_refresh();
void keyboard_resume_capture();
void keyboard_pause_capture();
void keyboard_stop_capture();

void keyboard_start_capture_numeric(void (*callback)(int));
void keyboard_stop_capture_numeric();

int keyboard_input_is_accepted();
int keyboard_is_capturing();
int keyboard_is_capturing_buffer(const uint8_t* text);
int keyboard_is_insert();
int keyboard_cursor_position();
int keyboard_offset_start();
int keyboard_offset_end();

void keyboard_return();

void keyboard_backspace();
void keyboard_delete();
void keyboard_insert();

void keyboard_left();
void keyboard_right();
void keyboard_home();
void keyboard_end();

void keyboard_text(const char* text_utf8);