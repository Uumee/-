#ifndef __FPSMANAGER_H
#define __FPSMANAGER_H

class FPSManager{
private:
	//����t���[�����Ăяo���ꂽ�������i�[ �P�ʂ�ms
	//�����l��0
	int time;

	//��ƂȂ鎞��
	int count0t;

	//�e�t���[���Ԃ̌o�ߎ��� �傫����fps�̔z��ɂȂ�
	//�����l��fps�̒l
	int *fpsCount;

	//���퓮�쎞��FPS���i�[
	//�����l��60
	unsigned char fps;

	//�o�߂����t���[�������L�^���邽�߂̕ϐ�
	//�����l��0
	unsigned char flameCount;


	static FPSManager *instance;

	FPSManager();
	~FPSManager();
public:
	static FPSManager& getInstance();
	static void deleteInstance();

	//FPS���v�����Afps��FPS�ɂȂ�悤�A�X���[�v�����s
	void run();

	//FPS��ݒ�
	//fpsCount��V����FPS���̑傫���ɂ��A�l��������
	void setFPS(int setFps);

	//���퓮�쎞��FPS���擾
	int getFPS();

	//�ŋ߂�fps�t���[�����̕��ς�FPS���擾
	//fps���ݒ肳��ĂȂ����0��Ԃ�
	double getAveFPS();
};
#endif
