#include "BodyManager.h"
#include <ConsoleEngine/EngineCore.h>
#include "Body.h"

Body* BodyManager::CurBody = nullptr;

void BodyManager::Update()
{
	if (nullptr != CurBody)
	{
		return;
	}

	std::list<ConsoleObject*> AllList = GetCore()->GetUpdateGroup();

	int ScreenX = GetCore()->Screen.GetScreenX();
	int ScreenY = GetCore()->Screen.GetScreenY();

	// ȭ�� ��ü������ ����Ʈ �ȿ� ��´�.
	std::list<int2> AllRange;
	// 00, 01, 10, 11
	{
		for (int y = 0; y < ScreenY; y++)
		{
			for (int x = 0; x < ScreenX; x++)
			{
				AllRange.push_back({ x, y });
			}
		}
	}


	// ������Ʈ�� �����ϴ� ��ġ�� �����.
	{
		std::list<ConsoleObject*>::iterator StartIter = AllList.begin();
		std::list<ConsoleObject*>::iterator EndIter = AllList.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			ConsoleObject* Object = *StartIter;

			if (nullptr == Object)
			{
				MsgBoxAssert("������Ʈ�� nullptr�� �༮�� �ֽ��ϴ�.");
			}

			AllRange.remove(Object->GetPos());
		}
	}

	AllRange;
	// 00, 10, 11
	//     ^

	{
		int RandomValue = rand() % AllRange.size();

		std::list<int2>::iterator StartIter = AllRange.begin();

		int2 CreateBodyPos = { 0, 0 };
		for (size_t i = 0; i < RandomValue; i++)
		{
			++StartIter;
		}
		CreateBodyPos = *StartIter;

		// ������ ��ġ�� ���������Ƿ�
		CurBody = GetCore()->CreateObject<Body>();
		CurBody->SetRenderChar('#');
		CurBody->SetPos(CreateBodyPos);
	}
}