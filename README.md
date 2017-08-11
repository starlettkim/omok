# omok
영재교육원 담당 교수님이 조교보고 만들라고 해서 만드는 오목 프로그램. 교수님이 대충 만들라고 하셔서 정말 대충 만들기로 했다.

## Requirements
Linux (Ubuntu 14.04 LTS에서 정상작동 확인)
C++11 이상을 컴파일할 수 있는 C++ 컴파일러

## Usage
$ make

$ ./fight

다른 프로그램과 붙으려면 Makefile을 수정하면 된당

## 파일 설명

- [AI.cpp](https://github.com/starlettkim/omok/blob/master/AI.cpp): 
상대방이 돌을 놓음에 따라, AI가 자동으로 돌을 놓는 프로그램.

- [refree.cpp](https://github.com/starlettkim/omok/blob/master/refree.cpp):
심판 프로그램

- [pipe.py](https://github.com/starlettkim/omok/blob/master/pipe.py)
player1, player2, 심판 프로그램 사이에서 표준 입/출력으로 데이터를 주고받는 프로그램.

- [fight.cpp](https://github.com/starlettkim/omok/blob/master/fight.cpp)
게임을 여러 번 구동하고 승률을 체크하기 위한 프로그램. 파이썬을 잘 몰라서 그냥 C++로 작성했다.
