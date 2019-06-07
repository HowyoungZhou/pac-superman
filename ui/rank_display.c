#include "rank_display.h"
#include "score.h"
#include <sprite.h>
#include <extgraph.h>
#include <vector2.h>
#include <engine.h>
#include <graphics.h>
#include <linked_list.h>
#include <game_controller.h>

static double cx, cy;

static void _Render(Sprite *this) {
    LinkedList rank = GetRank();
    RankListNode *node = rank.head;
    int i = 0;
    // 显示排行榜详情
    for (; node != NULL && i < MAX_RANK_LENGTH; node = node->next, i++) {
        RankListItem *item = node->element;
        MovePen(cx / 2 - 0.1, cy / 2 + 0.4 - 0.628 * i);
        DrawTextString(item->name);
        MovePen(cx / 2 + 2, cy / 2 + 0.4 - 0.63 * i);
        char score[MAX_SCORE_LENGTH + 1];
        sprintf(score, "%*d", MAX_SCORE_LENGTH, item->score);
        DrawTextString(score);
    }

}

Sprite *ConstructRankDisplaySprite() {
    cx = GetWindowWidth();
    cy = GetWindowHeight();

    Sprite *obj = ConstructSprite((Vector2) {cx / 2 - 3, cy * 0.15},
                                  (Vector2) {5, 3.5}, ZERO_VECTOR);

    obj->renderer.Render = _Render;

    return obj;
}