#pragma once
#include "DxLib.h"
#include "Key.h"

class titlepanel
{
private:
	
	int cnt,flg,bright,wait;
	int x,y,w,h;
	int endflag;
	int hBack,hStart;

public:
	titlepanel(void);
	~titlepanel(void);

	void run(KeyManager* key);
	void draw();
	bool isEnd();

	void init();

};

