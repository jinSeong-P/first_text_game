//
// Created by jspar on 25. 6. 19.
//
// World.h
#pragma once
#include <vector>
#include "Space.h"
#include "Action.h"

class World {
public:
    // 생성자: World 객체가 생성될 때 게임 월드를 초기화합니다.
    World();

    // 소멸자: World 객체가 파괴될 때 모든 메모리를 자동으로 해제합니다.
    ~World();

    // 현재 위치를 반환하는 getter
    Space* getCurrentLocation() const;

    // 현재 위치를 설정하는 setter
    void setCurrentLocation(Space* location);

    // 가능한 액션 목록을 반환하는 함수
    std::vector<Action> getAvailableActions() const;

private:
    std::vector<Space*> allSpaces;
    Space* currentLocation;
};
