#ifndef PAC_SUPERMAN_COLORS_H
#define PAC_SUPERMAN_COLORS_H

#include <stdint.h>
#include <genlib.h>

void DefineRGBColor(string name, uint32_t r, uint32_t g, uint32_t b);

void DefineHexColor(string name, uint32_t hex);

void DefineColors();

#endif //PAC_SUPERMAN_COLORS_H
