/// [Input]
// Direct input finctions
// 20098 syuki nishida
// 140507

/// Includes
#include "Input.h"
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)

/// ==============================Key============================== ///

#define REPEAT_COUNT		(30)

LPDIRECTINPUT8			gpDInput		= NULL;	//DirectInput�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	gpDIDevKeyboard	= NULL;	//DeviceObject�̃|�C���^
HWND					gHandle;
BYTE					gaKeyState[256];			//�L�[�{�[�h�̉�����
BYTE					gaKeyTrig[256];				//�L�[�{�[�h�̃g���K�[��
BYTE					gaKeyRelease[256];			//�L�[�{�[�h�̃����[�X��
BYTE					gaKeyRepeat[256];			//�L�[�{�[�h�̃����[�X��
int						gaKeyRepeatCnt[256];
bool					gInputFlg = true;

// DirectInput������
// �����@�F�C���X�^���X�@�n���h��
// �߂�l�F����
// 140110
HRESULT DirectInputModuleInit(HINSTANCE hInstance, HWND hWnd) {
	//�ϐ��錾
	HRESULT hr;

	gHandle = hWnd;

	// DirectInput�I�u�W�F�N�g�̍쐬
	if(gpDInput == NULL) {
		hr = DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&gpDInput,NULL);
		if(FAILED(hr)) {
			//���b�Z�[�W�{�b�N�X
			MessageBox(hWnd,"DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B","�G���[",MB_OK);
			return hr;
		}
	}
	return S_OK;
}

// DirectInput�I��
// �����@�Fvoid
// �߂�l�Fvoid
// 140110
void DirectInputModuleUninit(void) {

	// DirectInput�I�u�W�F�N�g�̊J��
	if(gpDInput != NULL) {
		gpDInput->Release();
		gpDInput = NULL;
	}

	// �f�o�C�X�I�u�W�F�N�g�̊J��
	if(gpDIDevKeyboard != NULL) {
		gpDIDevKeyboard->Unacquire();
		gpDIDevKeyboard->Release();
		gpDIDevKeyboard = NULL;
	}
}

// �L�[�{�[�h������
// �����@�Fvoid
// �߂�l�F����
// 140111
HRESULT DirectInputKeyboardInid(void) {
	//�ϐ��錾
	HRESULT hr;

	//DirectInput�����邩
	if(!gpDInput) {
		return E_FAIL;
	}

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = gpDInput->CreateDevice(GUID_SysKeyboard,&gpDIDevKeyboard,NULL);
	if(FAILED(hr)) {
		//���b�Z�[�W�{�b�N�X	
		MessageBox(gHandle,"�f�o�C�X�I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B","�G���[",MB_OK);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = gpDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr)) {
		//���b�Z�[�W�{�b�N�X
		MessageBox(gHandle,"�f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂����B","�G���[",MB_OK);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = gpDIDevKeyboard->SetCooperativeLevel(gHandle,(DISCL_FOREGROUND|DISCL_NONEXCLUSIVE));
	if(FAILED(hr)) {
		//���b�Z�[�W�{�b�N�X
		MessageBox(gHandle,"���a���[�h�̐ݒ�Ɏ��s���܂����B","�G���[",MB_OK);
		return hr;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	gpDIDevKeyboard->Acquire();

	gpDInput->Release();
	gpDInput = NULL;


	return S_OK;
}

//�u�L�[�{�[�h�̍X�V�����v
// �����@�Fvoid
// �߂�l�Fvoid
// 140110
void DirectInputKeyboardUpdate(void) {
	//�ϐ��錾
	BYTE aKeyState[256];

	//���擾
	if(SUCCEEDED(gpDIDevKeyboard->GetDeviceState(sizeof(aKeyState),&aKeyState[0]))) {
		//�L�[���X�V
		for(int nKey=0; nKey<256; nKey++) {
			//�L�[���쐬
			gaKeyRepeat[nKey]	=															//���s�[�g�̃g���K�[����
			gaKeyTrig[nKey]	= (aKeyState[nKey] ^ gaKeyState[nKey]) & aKeyState[nKey];		//�g���K�[�L�[
			gaKeyRelease[nKey]	= (aKeyState[nKey] ^ gaKeyState[nKey]) & gaKeyState[nKey];	//�����[�X�L�[
			gaKeyState[nKey]	= aKeyState[nKey];											//�v���X�L�[

			//���s�[�g�L�[
			if(gaKeyState[nKey] & 0x80){// �v���X�L�[��������Ă���
				if(gaKeyRepeatCnt[nKey] > REPEAT_COUNT){// �J�E���g�����܂��Ă���
					gaKeyRepeat[nKey] |= 0x80;	// ���s�[�g�L�[�쐬
				}else {// ���܂��ĂȂ�������
					gaKeyRepeatCnt[nKey]++;		// �J�E���g����
				}
			}else {//������ĂȂ�������
				gaKeyRepeatCnt[nKey] = 0;	//�J�E���g������
			}
		}
	}else {
		gpDIDevKeyboard->Acquire();
	}
}


// �L�[���擾
// �����@�F�L�[�A���[�h
// �߂�l�Ft/f
// 140110
bool GetDirectInputKeyboardInfo(int Key,int Mode) {
	if(!gInputFlg){
		return false;
	}

	//���[�h����
	switch(Mode) {
	case DI_MODE_PRESS:
		return gaKeyState[Key] & 0x80 ? true : false;
	case DI_MODE_TRIGG:
		return gaKeyTrig[Key] & 0x80 ? true : false;
	case DI_MODE_REPEAT:
		return gaKeyRepeat[Key] & 0x80 ? true : false;
	case DI_MODE_RELEASE:
		return gaKeyRelease[Key] & 0x80 ? true : false;
	}
	return false;
}

// �L�[�t���O�ݒ�
// �����@�F�t���O
// �߂�l�Fnone
// 140723
void	SetInputFlag(bool Flag){
	gInputFlg = Flag;
}


//=EOF=