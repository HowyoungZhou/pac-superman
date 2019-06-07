#include <stdlib.h>
#include "events.h"
#include "linked_list.h"

static void _KeyboardEventCallback(int key, int event);

static void _CharEventCallback(char c);

static void _MouseEventCallback(int x, int y, int button, int event);

static void _TimerEventCallback(int timerID);

LinkedList _keyboardEvents, _charEvents, _mouseEvents, _timerEvents;

static void _KeyboardEventCallback(int key, int event) {
    for (LinkedListNode *node = _keyboardEvents.head; node != NULL; node = node->next) {
        ((KeyboardEventCallback) node->element)(key, event);
    }
}

static void _CharEventCallback(char c) {
    for (LinkedListNode *node = _charEvents.head; node != NULL; node = node->next) {
        ((CharEventCallback) node->element)(c);
    }
}

static void _MouseEventCallback(int x, int y, int button, int event) {
    for (LinkedListNode *node = _mouseEvents.head; node != NULL; node = node->next) {
        ((MouseEventCallback) node->element)(x, y, button, event);
    }
}

static void _TimerEventCallback(int timerID) {
    for (LinkedListNode *node = _timerEvents.head; node != NULL; node = node->next) {
        ((TimerEventCallback) node->element)(timerID);
    }
}

void InitEvents() {
    registerCharEvent(_CharEventCallback);
    registerMouseEvent(_MouseEventCallback);
    registerKeyboardEvent(_KeyboardEventCallback);
    registerTimerEvent(_TimerEventCallback);
}

void RegisterKeyboardEvent(KeyboardEventCallback callback) {
    ListAddElement(&_keyboardEvents, callback);
}

void RegisterCharEvent(CharEventCallback callback) {
    ListAddElement(&_charEvents, callback);
}

void RegisterMouseEvent(MouseEventCallback callback) {
    ListAddElement(&_mouseEvents, callback);
}

void RegisterTimerEvent(TimerEventCallback callback) {
    ListAddElement(&_timerEvents, callback);
}

void CancelKeyboardEvent(KeyboardEventCallback callback) {
    ListRemoveElement(&_keyboardEvents, callback, PointerIdentifier);
}

void CancelCharEvent(CharEventCallback callback) {
    ListRemoveElement(&_charEvents, callback, PointerIdentifier);
}

void CancelMouseEvent(MouseEventCallback callback) {
    ListRemoveElement(&_mouseEvents, callback, PointerIdentifier);
}

void CancelTimerEvent(TimerEventCallback callback) {
    ListRemoveElement(&_timerEvents, callback, PointerIdentifier);
}