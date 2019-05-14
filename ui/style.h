#ifndef PAC_SUPERMAN_STYLE_H
#define PAC_SUPERMAN_STYLE_H

#include <genlib.h>

#define DEFAULT_STYLE (Style) {"Blue", "Blue", "Red", "Red", 0}

typedef struct {
    string borderColor;
    string textColor;
    string highlightedBorderColor;
    string highlightedTextColor;
    bool filled;
} Style;

#endif //PAC_SUPERMAN_STYLE_H
