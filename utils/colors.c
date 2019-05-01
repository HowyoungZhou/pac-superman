#include <extgraph.h>
#include <stdint.h>
#include "colors.h"

void DefineRGBColor(string name, uint32_t r, uint32_t g, uint32_t b) {
    DefineColor(name, r / 255., g / 255., b / 255.);
}

void DefineHexColor(string name, uint32_t hex) {
    DefineRGBColor(name, hex >> 16 & 0xFF, hex >> 8 & 0xFF, hex & 0xFF);
}

void DefineColors() {
    DefineHexColor("Pellet", 0xffb897);
}
