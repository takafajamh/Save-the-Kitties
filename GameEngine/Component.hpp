#pragma once


class Object;

class Component
{
public:

	Object* Holder = nullptr;

	bool KillMeIBegYou = false;
	virtual void Update() = 0;
	virtual ~Component(){}

};