#include "key.h"
#include "DxLib.h"
#include <memory.h>

//キーの状態の初期値を表す定数
#define INIT 0
//キーの状態に入る上限値を表す定数
#define LIMIT 32767
//キー入力を受け付けない時のキーの状態を表す定数
#define NONE -1

KeyManager::KeyManager():changeModeTime(1),updateTime(1){
	memset(keyState,0,sizeof(short int)*256);
}
KeyManager::~KeyManager(){}

//初期化(各キー状態の初期化):リセット処理と同義
void KeyManager::init(){
	memset(keyState,0,sizeof(short int)*256);
}

//呼び出された瞬間の各キーの状態によって，キーの状態を更新する
//これが呼び出されないとキー入力が認識されない
void KeyManager::run(){
	char k[256];
	GetHitKeyStateAll(k);
	for(int i=0;i<256;i++){
		if(keyState[i]==NONE) continue;	//そのキーの入力が受け付けられない状態であるなら飛ばす
		if(k[i]==1){//キーが押されている
			keyState[i]++;
			if(keyState[i]==LIMIT){
				keyState[i] = changeModeTime+(LIMIT-changeModeTime)%updateTime;
			}
		} else {
			keyState[i] = 0;
		}
	}
}

//キーが押下状態ならtrue(0以外を返す) (int キーに対応する定数)
int KeyManager::isPushed(int c){
	if(keyState[c]==NONE) return 0;
	return keyState[c];
}
//キーが離されているならtrue(0以外を返す) (int キーに対応する定数)
int KeyManager::isReleased(int c){
	if(keyState[c]==NONE) return 0;
	if(keyState[c]==0) return 1;
	return 0;
}
//キーが押された瞬間ならtrue(0以外を返す) (int キーに対応する定数)
int KeyManager::isPushedEdge(int c){
	if(keyState[c]==NONE) return 0;
	if(keyState[c]==1) return 1;
	return 0;
}

//キーが押されているフレーム数を取得する (int キーに対応する定数)
int KeyManager::getPushedTime(int c){
	if(keyState[c]==NONE) return 0;
	return keyState[c];
}

//changeModeTimeをcにする(unsigned int セットする値)
void KeyManager::setChangeModeTime(unsigned int c){
	changeModeTime = c;
}

//updateTImeをcにする(unsigned int セットする値)
void KeyManager::setUpdateTime(unsigned int c){
	updateTime = c;
}

//キーが押下状態であり，changeModeTimeを越え，かつ，updateTimeで割り切れるフレーム数分
//押されているならtrue。　あるいは，押された瞬間ならtrue (int キーに対応する定数)
int KeyManager::isPushedCont(int c){
	if(changeModeTime<=keyState[c] && ((keyState[c]-changeModeTime)%updateTime==0)){
		return 1;
	}
	return 0;
}

//特定のキーの入力を受け付けなくする(int キーに対応する定数)
void KeyManager::setNon(int c){
	keyState[c] = NONE;
}
//全てのキーの入力を受け付けなくする
void KeyManager::setNonAll(){
	for(int i=0;i<256;i++){
		keyState[i] = NONE;
	}
}

//特定のキーの入力を受け付ける状態にする (int キーに対応する定数)
void KeyManager::setOn(int c){
	keyState[c] = INIT;
}
//全てのキーの入力を受け付ける状態にする
void KeyManager::setOnAll(){
	memset(keyState,0,sizeof(short int)*256);
}
