//
// Created by jspar on 25. 6. 18.
//

#include <iostream>
#include <string>
#include <Windows.h>

enum class GameState {
    MAIN_MENU,
    PLAYING,
    QUIT
};

GameState showMainMenu();
GameState startGameLoop();
GameState showQuitMenu();

int main() {
    // Windows 콘솔에서 UTF-8을 사용하기 위한 설정
    SetConsoleOutputCP(CP_UTF8);

    GameState currentState = GameState::MAIN_MENU; // 게임 시작 시 초기 메뉴
    // 메인 루프
    while (true) {
        if (currentState == GameState::MAIN_MENU) {
            // 메인 메뉴를 보여주고, 사용자의 선택에 따라 다음 상태를 결정합니다.
            currentState = showMainMenu();
        } else if (currentState == GameState::PLAYING) {
            // 게임 플레이를 시작하고, 플레이가 끝나면 다음 상태를 반환받습니다.
            currentState = startGameLoop();
        } else if (currentState == GameState::QUIT) {
            std::cout << "\n게임을 종료합니다" << std::endl;
            break; // 종료 탈출
        }
    }
}

GameState showMainMenu() {
    std::cout << "================================" << std::endl;
    std::cout << "      나의 첫 텍스트 게임" << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << "        1. 게임 시작" << std::endl;
    std::cout << "        2. 게임 종료" << std::endl;
    std::cout << "================================" << std::endl;

    while (true) {
        std::cout << "선택> ";
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            return GameState::PLAYING; // '게임 시작'을 선택했으니 PLAYING 상태로 전환
        } else if (choice == "2") {
            return GameState::QUIT; // '게임 종료'를 선택했으니 QUIT 상태로 전환
        } else {
            std::cout << "잘못된 입력입니다. 1 또는 2를 입력해주세요." << std::endl;
        }
    }
}

GameState startGameLoop() {
    // 게임 루프 시작
    while (true) {
        std::cout << "> "; // 사용자 입력을 기다린다는 프롬프트 출력

        std::string command;
        std::getline(std::cin, command); // 한 줄 전체를 입력받음

        // 게임 종료 조건
        if (command == "quit") {
            // "quit" 명령을 받으면, 종료 메뉴를 보여주고 그 선택 결과를 반환한다.
            return showQuitMenu();
        }

        // 기본적인 반응
        std::cout << "'" << command << "'라고 입력하셨습니다." << std::endl;
    }
}

GameState showQuitMenu() {
    std::cout << "================================" << std::endl;
    std::cout << "        정말로 종료하시겠습니까?" << std::endl;
    std::cout << "        1. 취소" << std::endl;
    std::cout << "        2. 종료" << std::endl;
    std::cout << "================================" << std::endl;

    while (true) {
        std::cout << "선택> ";
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            return GameState::PLAYING; // '취소'을 선택했으니 PLAYING 상태로 전환
        } else if (choice == "2") {
            return GameState::QUIT; // '종료'를 선택했으니 QUIT 상태로 전환
        } else {
            std::cout << "잘못된 입력입니다. 1 또는 2를 입력해주세요." << std::endl;
        }
    }
}



