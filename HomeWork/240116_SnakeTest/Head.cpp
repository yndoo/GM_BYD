#include "Head.h"
#include <conio.h>
#include <ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"

// 
// 1. ���� Ư�� �������� �����ߴٸ� ���� �Է¶��� �� �ݴ�������δ� ������ ����.
//    ���� �̵��ϴ� ������ �ݴ�������δ� ���� �ȵȴ�.
// 2. ���� �̵��� �ؼ� CurBody�� ȹ���ߴٸ� �� �������� �� �ٵ�� ���� ����;� �Ѵ�.

void Head::Move() {
	std::list<Part*>::iterator StartIter = Bodies.begin();
	std::list<Part*>::iterator EndIter = Bodies.end();

	int2 FirstValue;
	int2 SecondValue;

	// ������ ���鼭 ��ġ�� �ڷ� �о��ٰ���
	for (; StartIter != EndIter; StartIter++) {
		// 
		if (StartIter != Bodies.begin()) {
			SecondValue = (*StartIter)->GetPos();
			(*StartIter)->SetPos(FirstValue);
			FirstValue = SecondValue;
		}
		else {	//StartIter == Bodies.begin()
			// ���� �Ǿ�
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

	// ��� ������ ���Ƶ� ������ �����̴� ���� ���� �뵵
	bool CanMove = false;

	int2 PrevDir = GetPrevDir();

	// ��� �̵�
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
		MsgBoxAssert("������ �ִ� �ٵ� �������� �ʽ��ϴ�.");
		return;
	}

	// CurBody�� ���̰�����
	// ������ ���ڷ� ��������ؾ���
	Body* CurBody = BodyManager::GetCurBody();

	if (CurBody->GetPos() == GetPos())	// CurBody �Ծ��� ��
	{
		if (Bodies.size() == 0) {
			CurBody->SetPos(GetPrevPos());
			Bodies.push_back(CurBody);
		}
		else {	// ���� ������ �̹� ���� ��
			// CurBody�� ���� ���� �־��ְ� ��ü ��ġ �ٲ��ֱ�
			Bodies.push_back(CurBody);
			Move();
		}
		BodyManager::ResetBody();
	}
	// ���� ���� �ʰ� �����ٴϴ� ��
	else { 
		if (CanMove) {
			Move();
		}
	}
	
}