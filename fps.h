#ifndef __FPSMANAGER_H
#define __FPSMANAGER_H

class FPSManager{
private:
	//あるフレームが呼び出された時刻を格納 単位はms
	//初期値は0
	int time;

	//基準となる時間
	int count0t;

	//各フレーム間の経過時間 大きさがfpsの配列になる
	//初期値はfpsの値
	int *fpsCount;

	//正常動作時のFPSを格納
	//初期値は60
	unsigned char fps;

	//経過したフレーム数を記録するための変数
	//初期値は0
	unsigned char flameCount;


	static FPSManager *instance;

	FPSManager();
	~FPSManager();
public:
	static FPSManager& getInstance();
	static void deleteInstance();

	//FPSを計測し、fpsのFPSになるよう、スリープを実行
	void run();

	//FPSを設定
	//fpsCountを新たなFPS分の大きさにし、値を初期化
	void setFPS(int setFps);

	//正常動作時のFPSを取得
	int getFPS();

	//最近のfpsフレーム分の平均のFPSを取得
	//fpsが設定されてなければ0を返す
	double getAveFPS();
};
#endif
