#include "namepanel.h"


namepanel::namepanel(void){

	x=0;y=0;
	bright=0;
	cnt=0;flg=0;
	hBack=LoadGraph("pic/back2.png");
	hName=LoadGraph("pic/nameinput.png");
	hName2=LoadGraph("pic/namecharcter.png");



}


namepanel::~namepanel(void){
}


void namepanel::run(KeyManager* key){

	bool a=false;

	if(flg==0)bright+=10;
	if(bright>=255)flg=1;
	if(flg==1)if((KeyInputString(200,380,20,name,false))==0)flg=2;
	if(flg==2)bright-=10;
	if(bright<=0 && flg==2)flg=3;
}





void namepanel::draw(){

	SetDrawBright(bright,bright,bright);
	
		for(x=0;x<640;x+=96)for(y=0;y<480;y+=96)DrawGraph(x,y,hBack,true);

		DrawGraph(0,360,hName,true);
		DrawGraph(0,120,hName2,true);

	SetDrawBright(255,255,255);
}

bool namepanel::isEnd(){
	if(flg==3)return true;
	else return false;
}