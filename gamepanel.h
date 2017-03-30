#pragma once

#include "DxLib.h"
#include "key.h"
#include "dat/def.h"

class gamepanel
{
private:

	FILE *fp;

	int flg2,max;
	int red,green,blue;
	int flg,num,cnt,wait,wait2;
	char w;
	int dat[2][STUDENT_MAX];

	int hBack,hBack2;

	LPCSTR font;

public:
	gamepanel(void);
	~gamepanel(void);

	void run(KeyManager* key);
	void draw();
	void filewrite();
	void fileread();
	bool isEnd();
	void init();
	void save();
	void rest_check();
	void max_check();
};

