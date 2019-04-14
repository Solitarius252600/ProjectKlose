/**
* @file MyApp.h
* @brief �Ǝ������N���X
* @author EtuCho
* @date 2019/04/14
* @details ����̓Ǝ������AD3D11App���p��
*/
#include "D3D11App.h"

#ifndef INCLUDE_MYAPP
#define INCLUDE_MYAPP


/**
* @brief �}�C�A�v���N���X
* @details �Ǝ������������Œ�`
*/
class MyApp : public D3D11App
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	MyApp();
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~MyApp();
	/**
	* @fn HRESULT Initialize(HINSTANCE hInstance, int nCmdShow)
	* @brief ������
	*/
	virtual HRESULT Initialize(HINSTANCE hInstance, int nCmdShow);
	/**
	* @fn void Render()
	* @brief �`��
	*/
	virtual void Render();
	/**
	* @fn void Update()
	* @brief �X�V
	*/
	virtual void Update(float dt);

private:

};

#endif // !INCLUDE_MYAPP