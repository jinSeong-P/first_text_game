//
// Created by jspar on 25. 6. 18.
//
#include <iostream>
#include <vector>
#include <limits>
#include <Windows.h>

#include "Space.h"
#include "Action.h"
#include "World.h"

enum class GameState {
    MAIN_MENU,
    PLAYING,
    QUIT
};

GameState showMainMenu();

void printLocationInfo(const World& world);
GameState startGameLoop(World& world);  // startGameLoop는 World의 참조를 받음


GameState showQuitMenu();


int main() {
    // Windows 콘솔에서 UTF-8을 사용하기 위한 설정
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    GameState currentState = GameState::MAIN_MENU; // 게임 시작 시 초기 메뉴
    // 메인 루프
    while (true) {
        if (currentState == GameState::MAIN_MENU) {
            // 메인 메뉴를 보여주고, 사용자의 선택에 따라 다음 상태를 결정합니다.
            currentState = showMainMenu();
        } else if (currentState == GameState::PLAYING) {
            // "게임 시작"을 선택하면 World 객체를 '스택'에 생성
            World gameWorld;
            // 게임 플레이를 시작하고, 플레이가 끝나면 다음 상태를 반환받습니다.
            currentState = startGameLoop(gameWorld);
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

        switch (stoi(choice)) {
            case 1:
                return GameState::PLAYING; // '게임 시작'을 선택했으니 PLAYING 상태로 전환
            case 2:
                return GameState::QUIT; // '게임 종료'를 선택했으니 QUIT 상태로 전환
            default:
                std::cout << "잘못된 입력입니다. 선택 가능한 숫자를 입력해주세요." << std::endl;
        }
    }
}

// startGameLoop는 World의 참조를 받음
GameState startGameLoop(World& world) {
    // world를 전달받아 사용하기만 하면 됩니다.

    printLocationInfo(world);

    // 게임 루프 시작
    while (true) {
        // 1. 현재 상황에서 가능한 액션 목록 생성
        std::vector<Action> availableActions = world.getAvailableActions();

        std::cout << "\n----------- 무엇을 할까? -----------" << std::endl;
        for (int i = 0; i < availableActions.size(); ++i) {
            std::cout << "  " << i + 1 << ". " << availableActions[i].description << std::endl;
        }
        std::cout << "------------------------------------" << std::endl;

        // 2. 사용자 입력을 안전하게 받습니다.
        std::cout << "> ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // 3. 유효한 입력인지 확인합니다.
        if (choice < 1 || choice > availableActions.size()) {
            std::cout << "잘못된 선택입니다. 목록에 있는 번호를 입력해주세요." << std::endl;
            continue; // 루프의 처음으로 돌아가 다시 입력을 받습니다.
        }

        const Action& selectedAction = availableActions[choice - 1];

        // 4. 선택된 액션을 처리합니다.
        switch (selectedAction.type) {
            case ActionType::LOOK:
                printLocationInfo(world); // 헬퍼 함수 호출로 중복 제거
                break;

            case ActionType::MOVE: {
                Space* nextSpace = world.getCurrentLocation()->getExit(selectedAction.argument);
                world.setCurrentLocation(nextSpace);

                std::cout << "\n... " << selectedAction.argument << "(으)로 이동합니다 ...\n" << std::endl;
                printLocationInfo(world); // 이동 후, 바뀐 위치 정보 출력
                break;
            }

            case ActionType::QUIT: {
                GameState newState = showQuitMenu();
                // 사용자가 '취소'가 아닌, 진짜 '종료'를 원할 때만
                if (newState == GameState::QUIT) {
                    // startGameLoop를 끝내고 '메인 메뉴' 상태로 돌아가도록 설정
                    return GameState::MAIN_MENU;
                }
                // '취소'를 선택했다면, 아무 일도 일어나지 않고 루프가 계속됩니다.
                break;
            }
        } // end of switch
    } // end of while
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

void printLocationInfo(const World& world) {
    Space* currentLocation = world.getCurrentLocation();
    if (currentLocation) { // currentLocation이 nullptr이 아닌지 확인 (안전장치)
        std::cout << "------------------------------------" << std::endl;
        std::cout << "현재 위치: " << currentLocation->getName() << std::endl;
        std::cout << currentLocation->getDescription() << std::endl;
        std::cout << "------------------------------------" << std::endl;
    }
}



