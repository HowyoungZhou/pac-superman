#ifndef PAC_SUPERMAN_EVENTS_H
#define PAC_SUPERMAN_EVENTS_H

#include <graphics.h>

void InitEvents();

void RegisterKeyboardEvent(KeyboardEventCallback callback);

void RegisterCharEvent(CharEventCallback callback);

void RegisterMouseEvent(MouseEventCallback callback);

void RegisterTimerEvent(TimerEventCallback callback);

void CancelKeyboardEvent(KeyboardEventCallback callback);

void CancelCharEvent(CharEventCallback callback);

void CancelMouseEvent(MouseEventCallback callback);

void CancelTimerEvent(TimerEventCallback callback);

#endif //PAC_SUPERMAN_EVENTS_H
