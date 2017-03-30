#include "DxLib.h"
#include "fps.h"

#include "key.h"
#include "titlepanel.h"
#include "namepanel.h"
#include "gamepanel.h"
#include "dat/def.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

//ゲームの状態を定義
#define GAMEMODE_START 0
#define GAMEMODE_NAME 1
#define GAMEMODE_GAME 2

#define _CRT_SECURE_NO_WARNINGS 

//関数のプロトタイプ宣言
int init();		//DxLibの初期化処理を行う（必ず最初に実行すること）　初期化が成功したなら0を，失敗したなら-1を返す

//関数の実体を定義
int init(){
	SetOutApplicationLogValidFlag( false );	//システムログを吐き出さないように設定
	ChangeWindowMode(WINDOW_SIZE);		//ウインドウモードでゲーム画面を表示する
	SetGraphMode(WINDOW_WIDTH,WINDOW_HEIGHT,32); //画面サイズとカラーモード(Trueカラー[16bitカラー]・フルカラー[32bitカラー])を設定
	// ライブラリの初期化　DxLib_Init()が-1を返す場合，初期化は失敗したということなので-1を返す
	if( DxLib_Init() < 0 ){
		return -1 ;
	}
	return 0; //初期化に成功したなら0を返す
}


// WinMain
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	if(init()==-1){
		exit(1); //初期化に失敗した場合，プログラムを終了する
	}
	// 描画先を裏画面にする
	SetDrawScreen( DX_SCREEN_BACK ) ;

	//スリープ処理用のインスタンスを宣言
	FPSManager &fps = FPSManager::getInstance();
	fps.setFPS(60);

	//キーボードの入力受取り用インスタンスを宣言
	KeyManager key;
	key.init();		//KeyManagerインスタンスの初期化

	//ゲームのモードを格納
	//GAMEMODE_SHOOTING:シューティングゲームを動かす
	//GAMEMODE_CLEAR:ゲームクリア画面を描画する
	int gameMode = GAMEMODE_START;

	//ゲーム画面のインスタンスを宣言
	//gamepanel game;
	titlepanel ti;
	gamepanel gm;

	// ＥＳＣキーが押されるか、ウインドウが閉じられるまでループ
	while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 ){
		ClearDrawScreen();	// 画面をクリア
		key.run();	//キーボードの入力を取得

		switch(gameMode){//ゲームモードによって処理を変える
		case GAMEMODE_START:
			ti.run(&key);
			ti.draw();
			if(ti.isEnd())gameMode=GAMEMODE_GAME;
			break;
		case GAMEMODE_GAME:
			gm.run(&key);
			gm.draw();
			if(gm.isEnd()){
				ti.init();
				gm.init();
				gameMode=GAMEMODE_START;
			}
			break;
		}

		fps.run();	//スリープ
		ScreenFlip() ;	// 裏画面の内容を表画面に反映
	}

	// ライブラリの後始末
	DxLib_End() ;
	// プログラム終了
	return 0 ;
}
