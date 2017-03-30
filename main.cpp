#include "DxLib.h"
#include "fps.h"

#include "key.h"
#include "titlepanel.h"
#include "namepanel.h"
#include "gamepanel.h"
#include "dat/def.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

//�Q�[���̏�Ԃ��`
#define GAMEMODE_START 0
#define GAMEMODE_NAME 1
#define GAMEMODE_GAME 2

#define _CRT_SECURE_NO_WARNINGS 

//�֐��̃v���g�^�C�v�錾
int init();		//DxLib�̏������������s���i�K���ŏ��Ɏ��s���邱�Ɓj�@�����������������Ȃ�0���C���s�����Ȃ�-1��Ԃ�

//�֐��̎��̂��`
int init(){
	SetOutApplicationLogValidFlag( false );	//�V�X�e�����O��f���o���Ȃ��悤�ɐݒ�
	ChangeWindowMode(WINDOW_SIZE);		//�E�C���h�E���[�h�ŃQ�[����ʂ�\������
	SetGraphMode(WINDOW_WIDTH,WINDOW_HEIGHT,32); //��ʃT�C�Y�ƃJ���[���[�h(True�J���[[16bit�J���[]�E�t���J���[[32bit�J���[])��ݒ�
	// ���C�u�����̏������@DxLib_Init()��-1��Ԃ��ꍇ�C�������͎��s�����Ƃ������ƂȂ̂�-1��Ԃ�
	if( DxLib_Init() < 0 ){
		return -1 ;
	}
	return 0; //�������ɐ��������Ȃ�0��Ԃ�
}


// WinMain
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	if(init()==-1){
		exit(1); //�������Ɏ��s�����ꍇ�C�v���O�������I������
	}
	// �`���𗠉�ʂɂ���
	SetDrawScreen( DX_SCREEN_BACK ) ;

	//�X���[�v�����p�̃C���X�^���X��錾
	FPSManager &fps = FPSManager::getInstance();
	fps.setFPS(60);

	//�L�[�{�[�h�̓��͎���p�C���X�^���X��錾
	KeyManager key;
	key.init();		//KeyManager�C���X�^���X�̏�����

	//�Q�[���̃��[�h���i�[
	//GAMEMODE_SHOOTING:�V���[�e�B���O�Q�[���𓮂���
	//GAMEMODE_CLEAR:�Q�[���N���A��ʂ�`�悷��
	int gameMode = GAMEMODE_START;

	//�Q�[����ʂ̃C���X�^���X��錾
	//gamepanel game;
	titlepanel ti;
	gamepanel gm;

	// �d�r�b�L�[��������邩�A�E�C���h�E��������܂Ń��[�v
	while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 ){
		ClearDrawScreen();	// ��ʂ��N���A
		key.run();	//�L�[�{�[�h�̓��͂��擾

		switch(gameMode){//�Q�[�����[�h�ɂ���ď�����ς���
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

		fps.run();	//�X���[�v
		ScreenFlip() ;	// ����ʂ̓��e��\��ʂɔ��f
	}

	// ���C�u�����̌�n��
	DxLib_End() ;
	// �v���O�����I��
	return 0 ;
}
