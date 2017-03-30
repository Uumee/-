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


//FPS���v�����Afps��FPS�ɂȂ�悤�A�X���[�v�����s
void FPSManager::run(){
	if(fps==0) return;
	int term,gnt;

	if(flameCount==0){	//fps�t���[����1��ڂȂ�
		if(time==0){	//���S�ɍŏ��Ȃ�܂��Ȃ�
			term=0;
			time = GetNowCount();
		} else{			//�O��L�^�������Ԃ����Ɍv�Z
			term=count0t+1000-GetNowCount();
		}
	} else {			//�҂ׂ�����=���݂���ׂ�����-���݂̎���
		term = (int)(count0t+flameCount*(1000.0/fps))-GetNowCount();
	}
	if(term>0){			//�҂ׂ����Ԃ����҂�
		Sleep(term);
	}
	gnt=GetNowCount();

	if(flameCount==0){//fps�t���[����1�x������
		count0t=gnt;
	}
	fpsCount[flameCount]=gnt-time;//�P���������Ԃ��L�^
	time=gnt;
	flameCount = (++flameCount)%fps ;
}

//FPS��ݒ�
//fpsCount��V����FPS���̑傫���ɂ��A�l��������
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
//���퓮�쎞��FPS���擾
int FPSManager::getFPS(){
	return fps;
}
//�ŋ߂�fps�t���[�����̕��ς�FPS���擾
double FPSManager::getAveFPS(){
	if(fps==0) return 0.0;
	double re = 0.0;
	for(unsigned char i=0;i<fps;i++){
		re += fpsCount[i];
	}
	return 1000.0/(re/(double)fps);
}
