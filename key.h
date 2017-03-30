#ifndef __KEYMANAGER_H
#define __KEYMANAGER_H

class KeyManager{
private:
	//各キーの状態を格納する配列 256個の要素を全て使う訳ではない
	//初期値はINIT
	short int keyState[256];

	//キーを連続入力状態に移行するフレーム数
	//初期値は1
	unsigned short int changeModeTime;

	//キーが連続入力モードの時，キーの入力が再び押された状態だと認識するフレーム数
	//初期値は1
	unsigned short int updateTime;

public:
	KeyManager();
	~KeyManager();

	//初期化(各キー状態の初期化):リセット処理と同義
	void init();

	//呼び出された瞬間の各キーの状態によって，キーの状態を更新する
	//これが呼び出されないとキー入力が認識されない
	 void run();

	//キーが押下状態ならtrue(0以外を返す) (int キーに対応する定数)
	int isPushed(int c);
	//キーが離されているならtrue(0以外を返す) (int キーに対応する定数)
	int isReleased(int c);
	//キーが押された瞬間ならtrue(0以外を返す) (int キーに対応する定数)
	int isPushedEdge(int c);

	//キーが押されているフレーム数を取得する (int キーに対応する定数)
	int getPushedTime(int c);

	//changeModeTimeをcにする(unsigned int セットする値)
	void setChangeModeTime(unsigned int c);

	//updateTImeをcにする(unsigned int セットする値)
	void setUpdateTime(unsigned int c);

	//キーが押下状態であり，changeModeTimeを越え，かつ，updateTimeで割り切れるフレーム数分
	//押されているならtrue。　あるいは，押された瞬間ならtrue (int キーに対応する定数)
	int isPushedCont(int c);

	//特定のキーの入力を受け付けなくする(int キーに対応する定数)
	void setNon(int c);
	//全てのキーの入力を受け付けなくする
	void setNonAll();

	//特定のキーの入力を受け付ける状態にする (int キーに対応する定数)
	void setOn(int c);
	//全てのキーの入力を受け付ける状態にする
	void setOnAll();
};
#endif
