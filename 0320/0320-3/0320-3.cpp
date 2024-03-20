#include <iostream>
#include <string>
using namespace std;

int main() {
    // 학번과 이름 출력
    cout << "화면에 그림을 그리는 프로그램입니다." << endl;
    cout << "학번: 202327004" << endl;
    cout << "이름: 김근우" << endl;

    string binaryCode;
    int blockCode;

    // 사용자로부터 블록 코드를 입력 받음
    while (true) {
        cout << "\n화면에 그릴 블록 코드를 이진수로 입력해주세요 (프로그램 종료를 원하면 1000000 입력): ";
        cin >> binaryCode;

        // 프로그램 종료 여부 확인
        if (binaryCode == "1000000")
            break;

        // 입력된 이진수를 10진수로 변환
        blockCode = 0;
        int power = 1;
        for (int i = binaryCode.length() - 1; i >= 0; i--) {
            if (binaryCode[i] == '1')
                blockCode += power;
            power *= 2;
        }

        // 입력된 코드가 올바른지 확인
        if (blockCode != 1 && blockCode != 2 && blockCode != 4 && blockCode != 8 &&
            blockCode != 16 && blockCode != 32) {
            cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
            continue;
        }

        // 입력된 코드에 해당하는 색상의 블록을 출력
        if (blockCode == 1) {
            cout << "\x1b[37m"; // 흰색
        }
        else if (blockCode == 2) {
            cout << "\x1b[31m"; // 빨간색
        }
        else if (blockCode == 4) {
            cout << "\x1b[30;1m"; // 회색
        }
        else if (blockCode == 8) {
            cout << "\x1b[33m"; // 노란색
        }
        else if (blockCode == 16) {
            cout << "\x1b[0;33m"; // 갈색
        }
        else if (blockCode == 32) {
            cout << "\x1b[35m"; // 마젠타색
        }

        cout << "▉"; // 블록 출력
        cout << "\x1b[0m"; // 색상 초기화
    }

    cout << "\n프로그램을 종료합니다." << endl;

    return 0;
}
