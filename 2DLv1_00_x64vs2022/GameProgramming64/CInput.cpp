#include "CInput.h"
#include <stdio.h>

CInput::CInput()
{
	printf("入力インスタスが生まれました\n");
}

bool CInput::Key(char key)
{
	return GetAsyncKeyState(key) < 0;
}
