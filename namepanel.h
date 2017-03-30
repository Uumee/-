#pragma once

#include "DxLib.h"
#include "key.h"

class namepanel
{
private:

	int x,y,h,w;
	int cnt,flg;
	int bright;
	int hBack;
	int hName;
	int hName2;

	char name[256];


public:
	namepanel(void);
	~namepanel(void);

	void run(KeyManager* key);
	void draw();
	bool isEnd();


};

