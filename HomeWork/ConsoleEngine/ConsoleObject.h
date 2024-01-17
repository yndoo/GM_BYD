#pragma once
#include "ConsoleMath.h"
#include "ConsoleUpdater.h"

// 전방선언 
class ConsoleObject : public ConsoleUpdater
{
	friend class EngineCore;

public:
	ConsoleObject();
	ConsoleObject(const int2& _StartPos, char _RenderChar);
	// 소멸자 virtual 
	virtual ~ConsoleObject();

	int2 GetPos() const;
	char GetRenderChar() const;

	inline void SetRenderChar(char _Ch)
	{
		RenderChar = _Ch;
	}

	inline void SetPos(const int2& _Pos)
	{
		Pos = _Pos;
	}

	inline void AddPos(const int2& _Dir)
	{
		Pos += _Dir;
	}

	int2 GetPrevPos() {
		return PrevPos;
	}
	int2 GetPrevDir() {
		return PrevDir;
	}

	void SetPrevPos(int2 _Pos) {
		PrevPos = _Pos;
	}
	void SetPrevDir(int2 _Dir) {
		PrevDir = _Dir;
	}

	template<typename EnumType>
	ConsoleObject* Collision(EnumType _UpdateOrder)
	{
		return Collision(static_cast<int>(_UpdateOrder));
	}

	// 나랑 충돌한 오브젝트
	ConsoleObject* Collision(int _UpdateOrder);

protected:

private:

	int2 Pos = { 0, 0 };
	char RenderChar = '@';
	int2 PrevDir;
	int2 PrevPos;
};


