//
// Created by jspar on 25. 6. 18.
//
// Space.h
#pragma once
#include <string>
#include <map>

class Space {
public:
    // 생성자: 이름과 설명을 받아 공간을 생성
    Space(const std::string& name, const std::string& description);

    // 공간의 출구를 추가
    void addExit(const std::string& direction, Space* space);

    // 특정 방향으로 연결된 공간 객체의 포인터 반환, 없으면 nullptr 반환
    Space* getExit(const std::string& direction);

    const std::map<std::string, Space*>& getExits() const;

    // 공간의 설명 반환
    std::string getDescription() const; // const: 이 함수는 멤버 변수를 변경하지 않음을 명시

    // 공간의 이름 반환
    std::string getName() const;



private:
    std::string name;
    std::string description;
    std::map<std::string, Space*> exits; // "동쪽" -> Space 객체 포인터
};
