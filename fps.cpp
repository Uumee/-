#include "fps.h"
#include "DxLib.h"
#include <malloc.h>

FPSManager* FPSManager::instance = NULL;

FPSManager::FPSManager():fps(0),fpsCount(NULL){}
FPSManager::~FPSManager(){
	if(fpsCount!=NULL){
		free(fpsCount);
	}
}

FPSManager& FPSManager::getInstance(){
	if(instance==NULL){
		instance = new FPSManager();
	}
	return *instance;
}
void FPSManager::deleteInstance(){
	delete instance;
	instance = NULL;
}


//FPSを計測し、fpsのFPSになるよう、スリープを実行
void FPSManager::run(){
	if(fps==0) return;
	int term,gnt;

	if(flameCount==0){	//fpsフレームの1回目なら
		if(time==0){	//完全に最初ならまたない
			term=0;
			time = GetNowCount();
		} else{			//前回記録した時間を元に計算
			term=count0t+1000-GetNowCount();
		}
	} else {			//待つべき時間=現在あるべき時刻-現在の時刻
		term = (int)(count0t+flameCount*(1000.0/fps))-GetNowCount();
	}
	if(term>0){			//待つべき時間だけ待つ
		Sleep(term);
	}
	gnt=GetNowCount();

	if(flameCount==0){//fpsフレームに1度基準を作る
		count0t=gnt;
	}
	fpsCount[flameCount]=gnt-time;//１周した時間を記録
	time=gnt;
	flameCount = (++flameCount)%fps ;
}

//FPSを設定
//fpsCountを新たなFPS分の大きさにし、値を初期化
void FPSManager::setFPS(int setFps){
	if(! (0 <= setFps && setFps <= 255) ) return;
	fps = setFps;
	if(fps==0) return;
	if(fpsCount!=NULL){
		free(fpsCount);
	}
	if( (fpsCount = (int *)malloc(sizeof(int)*fps))==NULL ){
		fps = 0;
		return;
	}
	time = 0;
	flameCount = 0;
	if(fps==0) return;
	int setValue = (int)(1000.0/(double)fps);
	for(unsigned char i=0;i<fps;i++){
		fpsCount[i] = setValue;
	}
}
//正常動作時のFPSを取得
int FPSManager::getFPS(){
	return fps;
}
//最近のfpsフレーム分の平均のFPSを取得
double FPSManager::getAveFPS(){
	if(fps==0) return 0.0;
	double re = 0.0;
	for(unsigned char i=0;i<fps;i++){
		re += fpsCount[i];
	}
	return 1000.0/(re/(double)fps);
}
