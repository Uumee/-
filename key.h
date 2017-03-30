#ifndef __KEYMANAGER_H
#define __KEYMANAGER_H

class KeyManager{
private:
	//�e�L�[�̏�Ԃ��i�[����z�� 256�̗v�f��S�Ďg����ł͂Ȃ�
	//�����l��INIT
	short int keyState[256];

	//�L�[��A�����͏�ԂɈڍs����t���[����
	//�����l��1
	unsigned short int changeModeTime;

	//�L�[���A�����̓��[�h�̎��C�L�[�̓��͂��Ăщ����ꂽ��Ԃ��ƔF������t���[����
	//�����l��1
	unsigned short int updateTime;

public:
	KeyManager();
	~KeyManager();

	//������(�e�L�[��Ԃ̏�����):���Z�b�g�����Ɠ��`
	void init();

	//�Ăяo���ꂽ�u�Ԃ̊e�L�[�̏�Ԃɂ���āC�L�[�̏�Ԃ��X�V����
	//���ꂪ�Ăяo����Ȃ��ƃL�[���͂��F������Ȃ�
	 void run();

	//�L�[��������ԂȂ�true(0�ȊO��Ԃ�) (int �L�[�ɑΉ�����萔)
	int isPushed(int c);
	//�L�[��������Ă���Ȃ�true(0�ȊO��Ԃ�) (int �L�[�ɑΉ�����萔)
	int isReleased(int c);
	//�L�[�������ꂽ�u�ԂȂ�true(0�ȊO��Ԃ�) (int �L�[�ɑΉ�����萔)
	int isPushedEdge(int c);

	//�L�[��������Ă���t���[�������擾���� (int �L�[�ɑΉ�����萔)
	int getPushedTime(int c);

	//changeModeTime��c�ɂ���(unsigned int �Z�b�g����l)
	void setChangeModeTime(unsigned int c);

	//updateTIme��c�ɂ���(unsigned int �Z�b�g����l)
	void setUpdateTime(unsigned int c);

	//�L�[��������Ԃł���CchangeModeTime���z���C���CupdateTime�Ŋ���؂��t���[������
	//������Ă���Ȃ�true�B�@���邢�́C�����ꂽ�u�ԂȂ�true (int �L�[�ɑΉ�����萔)
	int isPushedCont(int c);

	//����̃L�[�̓��͂��󂯕t���Ȃ�����(int �L�[�ɑΉ�����萔)
	void setNon(int c);
	//�S�ẴL�[�̓��͂��󂯕t���Ȃ�����
	void setNonAll();

	//����̃L�[�̓��͂��󂯕t�����Ԃɂ��� (int �L�[�ɑΉ�����萔)
	void setOn(int c);
	//�S�ẴL�[�̓��͂��󂯕t�����Ԃɂ���
	void setOnAll();
};
#endif
