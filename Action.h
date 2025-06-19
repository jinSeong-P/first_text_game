//
// Created by jspar on 25. 6. 18.
//
#pragma once
#include <string>

enum class ActionType {
    LOOK,
    MOVE,
    GET_ITEM,
    QUIT,
    // ... 앞으로 추가될 액션들
};

// struct의 '정의'
// 다른 파일들이 Action 객체를 생성하고 멤버에 접근하려면 이 정의를 알아야 합니다.
struct Action {
    std::string description; // 화면에 표시될 텍스트 (예: "동쪽으로 이동한다")
    ActionType type;         // 이 액션의 종류
    std::string argument;    // 액션에 필요한 추가 정보 (예: 이동할 방향 "동쪽")
};
