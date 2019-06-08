#include <imgui.h>
#include <graphics.h>
#include <extgraph.h>
#include <sprite.h>
#include <engine.h>
#include <game_scene.h>
#include <game_controller.h>
#include <game_home_scene.h>
#include "end_game_box.h"

static inline void _DrawSaveButton(double x, double y, double w, double h);

static inline void _DrawHomeButton(double x, double y, double w, double h);

static inline void _DrawPlayAgainButton(double x, double y, double w, double h);

static inline void _DrawWinTextBox();

static inline void _DrawNewRecordTextBox();

static inline void _DrawLoseTextBox();

static int _GAMESTART = 0;
static char _name[MAX_NAME_LENGTH];
static double cx, cy;
static EndGameResult _result;
static bool _saved = false;

static inline void _DrawSaveButton(double x, double y, double w, double h) {
    if (!_saved && button(GenUIID(0), x, y, w, h, "Save")) {
        AddToRank(_name, GetScore());
        _saved = true;
    }
}

static inline void _DrawHomeButton(double x, double y, double w, double h) {
    if (button(GenUIID(0), x, y, w, h, "Home")) {
        ReplaceScene(ConstructHomeScene());
    }
}

static inline void _DrawPlayAgainButton(double x, double y, double w, double h) {
    if (button(GenUIID(0), x, y, w, h, "Play Again")) {
        NewGame();
    }
}

static inline void _DrawNewRecordTextBox() {
    cx = GetWindowWidth();
    cy = GetWindowHeight();
    double fH = GetFontHeight();

    //绘制新纪录对话框
    drawRectangle(cx / 2 - 2, cy / 2 - 1, 4, 2.5, 1);
    SetPenColor("Brown");
    int size = GetPointSize();
    SetPointSize(18);
    drawLabel(cx / 2 - TextStringWidth("New Record! Congratulations!") / 2, cy / 2 + 1, "New Record! Congratulations!");
    drawLabel(cx / 2 - TextStringWidth("Please enter your name.") / 2, cy / 2 + 0.7,
              "Please enter your name.");
    textbox(GenUIID(0), cx / 2 - 1.5, cy / 2, 3, fH * 2.5, _name, sizeof(_name));
    SetPointSize(size);
    _DrawSaveButton(cx / 2 - 0.9, cy / 2 - 0.8, 0.65, 0.35);
    _DrawHomeButton(cx / 2 - 0.15, cy / 2 - 0.8, 0.65, 0.35);
    _DrawPlayAgainButton(cx / 2 + 0.6, cy / 2 - 0.8, 0.9, 0.35);
}

static inline void _DrawLoseTextBox() {

    cx = GetWindowWidth();
    cy = GetWindowHeight();
    double fH = GetFontHeight();

    //绘制失败对话框
    drawRectangle(cx / 2 - 2, cy / 2 - 1, 4, 2.5, 1);
    SetPenColor("Brown");
    int size = GetPointSize();
    SetPointSize(18);
    drawLabel(cx / 2 - TextStringWidth("Your score is") / 2, cy / 2 + 1, "Your score is");
    drawLabel(cx / 2 - TextStringWidth("Good luck next time!") / 2, cy / 2, "Good luck next time!");
    SetPointSize(24);
    char score[MAX_SCORE_LENGTH + 1];
    sprintf_s(score, MAX_SCORE_LENGTH + 1, "%d", GetScore());
    drawLabel(cx / 2 - TextStringWidth(score) / 2, cy / 2 + 0.45, score);
    SetPointSize(size);
    _DrawHomeButton(cx / 2 - 0.15, cy / 2 - 0.8, 0.65, 0.35);
    _DrawPlayAgainButton(cx / 2 + 0.6, cy / 2 - 0.8, 0.9, 0.35);
}

static inline void _DrawWinTextBox() {

    cx = GetWindowWidth();
    cy = GetWindowHeight();
    double fH = GetFontHeight();

    //绘制胜利对话框
    drawRectangle(cx / 2 - 2, cy / 2 - 1, 4, 2.5, 1);
    SetPenColor("Brown");
    int size = GetPointSize();
    SetPointSize(18);
    drawLabel(cx / 2 - TextStringWidth("Your score is") / 2, cy / 2 + 1, "Your score is");
    drawLabel(cx / 2 - TextStringWidth("Congratulations!") / 2, cy / 2, "Congratulations!");
    SetPointSize(24);
    char score[MAX_SCORE_LENGTH + 1];
    sprintf_s(score, MAX_SCORE_LENGTH + 1, "%d", GetScore());
    drawLabel(cx / 2 - TextStringWidth(score) / 2, cy / 2 + 0.45, score);
    SetPointSize(size);
    _DrawHomeButton(cx / 2 - 0.15, cy / 2 - 0.8, 0.65, 0.35);
    _DrawPlayAgainButton(cx / 2 + 0.6, cy / 2 - 0.8, 0.9, 0.35);
}

void _Render() {
    switch (_result) {
        case WIN:
            _DrawWinTextBox();
            break;
        case LOSE:
            _DrawLoseTextBox();
            break;
        case NEW_RECORD:
            _DrawNewRecordTextBox();
            break;
        default:
            break;
    }
}

static void _Destruct(Sprite *this) {
    free(this->property);
    DestructSprite(this);
}

Sprite *ConstructEndGameBoxSprite(EndGameResult result) {
    cx = GetWindowWidth();
    cy = GetWindowHeight();

    Sprite *obj = ConstructSprite((Vector2) {cx - 2, cy - 1},
                                  (Vector2) {2, 2}, ZERO_VECTOR);
    _saved = false;
    _result = result;
    obj->Destruct = _Destruct;
    obj->renderer.Render = _Render;
    return obj;
}