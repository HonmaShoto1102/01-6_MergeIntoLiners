#ifndef KEYLOGER_H
#define KEYLOGER_H

//�L�[���͂̋L�^����

//�L�[���K�[�L�[�񋓌^
typedef enum KeyloggerKey_tag 
{
	KL_W,
	KL_S,
	KL_A,
	KL_D,
	KL_J,	
	//KL_DECISION = KL_ATTACK,
	//KL_SPACE,
	//KL_CANCEL = KL_SPECIAL,
	KL_K,
	KL_L,	
	KL_HOME,
	KL_PGUP,
	KL_PGDN,
	KL_END,
	KL_ENTER,
	KL_SPACE,
	KL_RIGHTSHIFT,
	KL_U,
	KL_MAX
}KeyloggerKey;
//�L�[���K�[���W���[���̏�����
void Keylogger_Initialize();
//�L�[���K�[���W���[���̏I������
void Keylogger_Finalize();
//�L�[���K�[���W���[���̍X�V
void Keylogger_Update();



//�L�[���͏�Ԃ̎擾
//
//�����F
//
//�߂�l�F������Ă�����true
//
bool keylogger_Press(KeyloggerKey kl);

//�L�[���͏�Ԃ̎擾(�������u��)
//
//�����F
//
//�߂�l�F������Ă�����true
//
bool keylogger_Trigger(KeyloggerKey kl);

//�L�[���͏�Ԃ̎擾(�������u��)
//
//�����F
//
//�߂�l�F�������u�Ԃ�������true
//
bool keylogger_Release(KeyloggerKey kl);



void Keylogger_RecordStart(int frame_max);
void Keylogger_RecordEnd();
void Keylogger_RecordLoad();
void Keylogger_RecordPlay();
bool Keylogger_IsRecordPlay();

#endif // !KEYLOGER_H

