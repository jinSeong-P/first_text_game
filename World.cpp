//
// Created by jspar on 25. 6. 19.
//
// World.cpp
#include "World.h"
#include <iostream>

// 생성자: 여기서 모든 방을 생성하고 연결합니다.
World::World() {
    std::cout << "[Debug] World 생성자 호출됨. 게임 월드를 생성합니다." << std::endl;

    Space* villageSquare = new Space("마을 광장", "사람들이 오가는 시끌벅적한 광장입니다.");
    Space* store = new Space("상점", "여러 가지 물건을 파는 상점입니다. 먼지 쌓인 포션이 보입니다.");
    Space* forestEntrance = new Space("숲 입구", "으스스한 기운이 감도는 숲의 입구입니다. 북쪽으로 길이 나 있습니다.");

    villageSquare->addExit("동쪽", store);
    villageSquare->addExit("북쪽", forestEntrance);
    store->addExit("서쪽", villageSquare);
    forestEntrance->addExit("남쪽", villageSquare);

    allSpaces = {villageSquare, store, forestEntrance};
    currentLocation = villageSquare; // 시작 위치 설정
}

// 소멸자: 여기서 모든 메모리를 책임지고 해제합니다!
World::~World() {
    std::cout << "[Debug] World 소멸자 호출됨. 모든 메모리를 해제합니다." << std::endl;
    for (Space* space : allSpaces) {
        delete space;
    }
    allSpaces.clear();
}

Space* World::getCurrentLocation() const {
    return currentLocation;
}

void World::setCurrentLocation(Space* location) {
    currentLocation = location;
}

std::vector<Action> World::getAvailableActions() const {
    std::vector<Action> actions;

    // 1. 현재 위치 정보 가져오기
    Space* location = this->getCurrentLocation();
    if (location == nullptr) return actions; // 예외 처리

    // 2. 기본 액션 추가
    actions.push_back({"주변을 둘러본다", ActionType::LOOK});

    // 3. 이동 액션 추가
    const auto& exits = location->getExits();
    for (const auto& pair : exits) {
        actions.push_back({pair.first + "(으)로 이동한다", ActionType::MOVE, pair.first});
    }

    // 4. 아이템 줍기 액션 추가 (나중에 구현)
    // if (!location->getItems().empty()) { ... }

    // 5. 종료 액션 추가
    actions.push_back({"메인 메뉴로 돌아간다", ActionType::QUIT});

    return actions;
}