#include "rank_display.h"
#include <sprite.h>
#include <extgraph.h>
#include <vector2.h>
#include <engine.h>
#include <graphics.h>
#include <linked_list.h>

static double cx,cy;

static LinkedList testrank={NULL,NULL,0};

static GameResult player1,player2,player3,player4,player5;

static void _Render(Sprite *this){

    int i;
    cx = GetWindowWidth();
    cy = GetWindowHeight();

    LinkedListNode *ptr = testrank.head;

    //显示排行榜详情（ps 通过testrank.length 无法正常循环？）
    for(i = 0 ; i < 5; i++){
        MovePen(cx/2 - 0.1, cy/2 + 0.4 - 0.628 * i);
        DrawTextString(((GameResult *)(ptr->element))->name);
        MovePen(cx/2 + 2, cy/2 + 0.4 - 0.63 * i);
        DrawTextString(((GameResult *)(ptr->element))->score);
        ptr = ptr -> next;
    }

}

static void _Destruct(Sprite *this) {
    free(this->property);
    DestructSprite(this);
}

Sprite *ConstructRankDisplaySprite(){

    cx = GetWindowWidth();
    cy = GetWindowHeight();

    Sprite *obj= ConstructSprite((Vector2){cx/2-3,cy*0.15},
                                 (Vector2){5,3.5},ZERO_VECTOR);

    obj->Destruct = _Destruct;
    obj->renderer.Render = _Render;

    player1.name = "Jack" ;
    player1.score = "100" ;
    player2.name = "Anne" ;
    player2.score = "60" ;
    player3.name = "Anne" ;
    player3.score = "60" ;
    player4.name = "Anne" ;
    player4.score = "60" ;
    player5.name = "Anne" ;
    player5.score = "60" ;
    AddElement(&testrank, &player1);
    AddElement(&testrank, &player2);
    AddElement(&testrank, &player3);
    AddElement(&testrank, &player4);
    AddElement(&testrank, &player5);

    return obj;
}