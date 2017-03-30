#include "key.h"
#include "DxLib.h"
#include <memory.h>

//�L�[�̏�Ԃ̏����l��\���萔
#define INIT 0
//�L�[�̏�Ԃɓ������l��\���萔
#define LIMIT 32767
//�L�[���͂��󂯕t���Ȃ����̃L�[�̏�Ԃ�\���萔
#define NONE -1

KeyManager::KeyManager():changeModeTime(1),updateTime(1){
	memset(keyState,0,sizeof(short int)*256);
}
KeyManager::~KeyManager(){}

//������(�e�L�[��Ԃ̏�����):���Z�b�g�����Ɠ��`
void KeyManager::init(){
	memset(keyState,0,sizeof(short int)*256);
}

//�Ăяo���ꂽ�u�Ԃ̊e�L�[�̏�Ԃɂ���āC�L�[�̏�Ԃ��X�V����
//���ꂪ�Ăяo����Ȃ��ƃL�[���͂��F������Ȃ�
void KeyManager::run(){
	char k[256];
	GetHitKeyStateAll(k);
	for(int i=0;i<256;i++){
		if(keyState[i]==NONE) continue;	//���̃L�[�̓��͂��󂯕t�����Ȃ���Ԃł���Ȃ��΂�
		if(k[i]==1){//�L�[��������Ă���
			keyState[i]++;
			if(keyState[i]==LIMIT){
				keyState[i] = changeModeTime+(LIMIT-changeModeTime)%updateTime;
			}
		} else {
			keyState[i] = 0;
		}
	}
}

//�L�[��������ԂȂ�true(0�ȊO��Ԃ�) (int �L�[�ɑΉ�����萔)
int KeyManager::isPushed(int c){
	if(keyState[c]==NONE) return 0;
	return keyState[c];
}
//�L�[��������Ă���Ȃ�true(0�ȊO��Ԃ�) (int �L�[�ɑΉ�����萔)
int KeyManager::isReleased(int c){
	if(keyState[c]==NONE) return 0;
	if(keyState[c]==0) return 1;
	return 0;
}
//�L�[�������ꂽ�u�ԂȂ�true(0�ȊO��Ԃ�) (int �L�[�ɑΉ�����萔)
int KeyManager::isPushedEdge(int c){
	if(keyState[c]==NONE) return 0;
	if(keyState[c]==1) return 1;
	return 0;
}

//�L�[��������Ă���t���[�������擾���� (int �L�[�ɑΉ�����萔)
int KeyManager::getPushedTime(int c){
	if(keyState[c]==NONE) return 0;
	return keyState[c];
}

//changeModeTime��c�ɂ���(unsigned int �Z�b�g����l)
void KeyManager::setChangeModeTime(unsigned int c){
	changeModeTime = c;
}

//updateTIme��c�ɂ���(unsigned int �Z�b�g����l)
void KeyManager::setUpdateTime(unsigned int c){
	updateTime = c;
}

//�L�[��������Ԃł���CchangeModeTime���z���C���CupdateTime�Ŋ���؂��t���[������
//������Ă���Ȃ�true�B�@���邢�́C�����ꂽ�u�ԂȂ�true (int �L�[�ɑΉ�����萔)
int KeyManager::isPushedCont(int c){
	if(changeModeTime<=keyState[c] && ((keyState[c]-changeModeTime)%updateTime==0)){
		return 1;
	}
	return 0;
}

//����̃L�[�̓��͂��󂯕t���Ȃ�����(int �L�[�ɑΉ�����萔)
void KeyManager::setNon(int c){
	keyState[c] = NONE;
}
//�S�ẴL�[�̓��͂��󂯕t���Ȃ�����
void KeyManager::setNonAll(){
	for(int i=0;i<256;i++){
		keyState[i] = NONE;
	}
}

//����̃L�[�̓��͂��󂯕t�����Ԃɂ��� (int �L�[�ɑΉ�����萔)
void KeyManager::setOn(int c){
	keyState[c] = INIT;
}
//�S�ẴL�[�̓��͂��󂯕t�����Ԃɂ���
void KeyManager::setOnAll(){
	memset(keyState,0,sizeof(short int)*256);
}
