#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <stdbool.h>
#include "example_sprite.h"
#include "sprite.h"

void Main() {
    InitGraphics();
    Sprite *obj = ConstructExampleSprite();
    obj->renderer.Render(obj);
    obj->Destruct(obj);
}
