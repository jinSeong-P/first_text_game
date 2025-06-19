//
// Created by jspar on 25. 6. 18.
//
#include "Space.h"

// 생성자 구현
Space::Space(const std::string& name, const std::string& description)
    : name(name), description(description) {
    // 생성자 초기화 리스트 사용
}

void Space::addExit(const std::string &direction, Space *space) {
    exits[direction] = space;
}

Space* Space::getExit(const std::string &direction) {
    if (exits.find(direction) != exits.end()) {
        // 있다면 해당 Space 포인터를 반환
        return exits[direction];
    }
    // 없다면 널 포인터(nullptr)를 반환
    return nullptr;
}

const std::map<std::string, Space*>& Space::getExits() const {
    return this->exits;
}

std::string Space::getDescription() const {
    return description;
}

std::string Space::getName() const {
    return name;
}



