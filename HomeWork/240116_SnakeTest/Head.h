#pragma once
#include "Part.h"
#include <list>

class Head : public Part
{

protected:
	void Update() override;
private:
	std::list<Part*> Bodies;
	void Move();
};

