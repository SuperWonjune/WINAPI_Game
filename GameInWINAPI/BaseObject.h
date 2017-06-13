#pragma once
class BaseObject
{
public:
	BaseObject();
	virtual ~BaseObject();

	int getX(void) { return _x; }
	int getY(void) { return _y; }

protected:
	int _x;
	int _y;
};

