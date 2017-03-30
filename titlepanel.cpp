#include "titlepanel.h"


titlepanel::titlepanel(void){
	x=0;y=0;wait=0;
	cnt=0;flg=0;
	bright=255;
	endflag=0;
	hBack=LoadGraph("pic/back1.png");
	hStart=LoadGraph("pic/start1.png");
	GetGraphSize(hBack,&w,&h);
}


titlepanel::~titlepanel(void){

}



void titlepanel::run(KeyManager* key){

	wait++;

	if(cnt>=255)flg=1;
	if(cnt<=30)flg=0;

	if(flg==0)cnt+=5;
	if(flg==1)cnt-=5;

	if(CheckHitKeyAll()!=0 && wait>60)endflag=1;
	if(endflag==1)bright-=10;

	if(bright<0)endflag=2;

}

void titlepanel::draw(){

	SetDrawBright(bright,bright,bright);
	
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	
			for(x=0;x<640;x+=96)for(y=0;y<480;y+=96)DrawGraph(x,y,hBack,true);
	
		if(endflag==0)SetDrawBlendMode(DX_BLENDMODE_ALPHA,cnt);

			if(wait>60)DrawGraph(0,240-h/2,hStart,true);

	SetDrawBright(255,255,255);
}

bool titlepanel::isEnd(){
	if(endflag==2)return 1;
	else return 0;
}

void titlepanel::init(){

	flg=0;
	bright=255;
	endflag=0;
	cnt=0;wait=0;

}