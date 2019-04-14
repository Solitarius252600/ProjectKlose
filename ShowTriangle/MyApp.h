/**
* @file MyApp.h
* @brief 独自処理クラス
* @author EtuCho
* @date 2019/04/14
* @details 今回の独自処理、D3D11Appを継承
*/
#include "D3D11App.h"

#ifndef INCLUDE_MYAPP
#define INCLUDE_MYAPP


/**
* @brief マイアプリクラス
* @details 独自処理をここで定義
*/
class MyApp : public D3D11App
{
public:
	/**
	* @brief コンストラクタ
	*/
	MyApp();
	/**
	* @brief デストラクタ
	*/
	virtual ~MyApp();
	/**
	* @fn HRESULT Initialize(HINSTANCE hInstance, int nCmdShow)
	* @brief 初期化
	*/
	virtual HRESULT Initialize(HINSTANCE hInstance, int nCmdShow);
	/**
	* @fn void Render()
	* @brief 描画
	*/
	virtual void Render();
	/**
	* @fn void Update()
	* @brief 更新
	*/
	virtual void Update(float dt);

private:

};

#endif // !INCLUDE_MYAPP