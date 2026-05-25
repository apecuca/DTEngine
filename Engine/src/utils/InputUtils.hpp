#ifndef DTENGINE_INPUTUTILS_H
#define DTENGINE_INPUTUTILS_H

namespace DTEngine
{

struct KeyboardEvent
{
public:
	KeyboardEvent() = default;
	KeyboardEvent(int _key, bool _pressed) :
		key(_key), pressed(_pressed)
	{ }

	int key;
	bool pressed;

};

}

#endif