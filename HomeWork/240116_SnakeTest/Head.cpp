#include "Head.h"
#include <conio.h>
#include <ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"

// 
// 1. 내가 특정 방향으로 진행했다면 다음 입력때는 그 반대방향으로는 갈수가 없다.
//    내가 이동하는 방향의 반대방향으로는 가면 안된다.
// 2. 내가 이동을 해서 CurBody를 획득했다면 그 다음부터 그 바디는 나를 따라와야 한다.

void Head::Move() {
	std::list<Part*>::iterator StartIter = Bodies.begin();
	std::list<Part*>::iterator EndIter = Bodies.end();

	int2 FirstValue;
	int2 SecondValue;

	// 몸통을 돌면서 위치를 뒤로 밀어줄거임
	for (; StartIter != EndIter; StartIter++) {
		// 
		if (StartIter != Bodies.begin()) {
			SecondValue = (*StartIter)->GetPos();
			(*StartIter)->SetPos(FirstValue);
			FirstValue = SecondValue;
		}
		else {	//StartIter == Bodies.begin()
			// 몸통 맨앞
			FirstValue = (*StartIter)->GetPos();
			(*StartIter)->SetPos(GetPrevPos());
		}

	}
}


void Head::Update()
{
	int InputCount = _kbhit();
	if (0 == InputCount)
	{
		return;
	}

	int Select = _getch();

	SetPrevPos(GetPos());
	//PrevPos = GetPos();

	// 헤드 움직임 막아도 꼬리는 움직이는 현상 막는 용도
	bool CanMove = false;

	int2 PrevDir = GetPrevDir();

	// 헤드 이동
	switch (Select)
	{
	case 'A':
	case 'a':
		if (PrevDir != Right) {
			AddPos(Left);
			SetPrevDir(Left);
			CanMove = true;
			//PrevDir = Left;
		}
		break;
	case 'S':
	case 's':
		if (PrevDir != Up) {
			AddPos(Down);
			SetPrevDir(Down);
			CanMove = true;
			//PrevDir = Down;
		}
		break;
	case 'W':
	case 'w':
		if (PrevDir != Down) {
			AddPos(Up);
			SetPrevDir(Up);
			CanMove = true;
			//PrevDir = Up;	
		}
		break;
	case 'D':
	case 'd':
		if (PrevDir != Left) {
			AddPos(Right);
			SetPrevDir(Right);
			CanMove = true;
			//PrevDir = Right;
		}
		break;
	case '1':
		GetCore()->EngineEnd();
		break;
	default:
		break;
	}

	if (nullptr == BodyManager::GetCurBody())
	{
		MsgBoxAssert("먹을수 있는 바디가 존재하지 않습니다.");
		return;
	}

	// CurBody가 먹이같은애
	// 먹으면 헤드뒤로 따라오게해야함
	Body* CurBody = BodyManager::GetCurBody();

	if (CurBody->GetPos() == GetPos())	// CurBody 먹었을 때
	{
		if (Bodies.size() == 0) {
			CurBody->SetPos(GetPrevPos());
			Bodies.push_back(CurBody);
		}
		else {	// 먹은 몸통이 이미 있을 때
			// CurBody를 몸통 끝에 넣어주고 전체 위치 바꿔주기
			Bodies.push_back(CurBody);
			Move();
		}
		BodyManager::ResetBody();
	}
	// 몸통 먹지 않고 지나다니는 중
	else { 
		if (CanMove) {
			Move();
		}
	}
	
}