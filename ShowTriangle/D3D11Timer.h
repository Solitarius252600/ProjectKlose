/**
* @file Timer.h
* @brief タイマークラス
* @author EtuCho
* @date 2019/04/14
* @details FPS計算とアプリケーション実行時間用クラス、読み込み回数少ないためメソッドは基本インライン展開
*/


#ifndef INCLUDE_D2D1TIMER
#define INCLUDE_D2D1TIMER

#include <sstream>
#include "Common.h"

/**
* @brief タイムを計るクラス
* @details FPS計算とDeltaTime計算
*/
class D3D11Timer
{
public:
	/**
	* @brief コンストラクタ
	*/
	D3D11Timer()
	{
		INT64 countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		m_secondsPerCount = 1.0 / (double)countsPerSec;
	}

	/**
	* @brief トータルタイム
	*/
	float TotalTime() const
	{
		if (m_stopped)
			return (float)(((m_stopTime - m_pausedTime) - m_baseTime)*m_secondsPerCount);
		else
			return (float)(((m_currTime - m_pausedTime) - m_baseTime)*m_secondsPerCount);
	}

	/**
	* @brief デルタタイム
	*/
	float DeltaTime() const { return (float)m_deltaTime; }

	/**
	* @brief ループする前に一回リセット
	*/
	void Reset()
	{
		INT64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_baseTime = currTime;
		m_prevTime = currTime;
		m_stopTime = 0;
		m_stopped = false;
	}

	/**
	* @brief スタート
	*/
	void Start()
	{
		INT startTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

		// ストップ状態なら実行
		if (m_stopped)
		{
			// 止まってる時間を計る
			m_pausedTime += (startTime - m_stopTime);
			// 一回リセット
			m_prevTime = startTime;
			// ストップ解除
			m_stopTime = 0;
			m_stopped = false;
		}
	}

	/**
	* @brief ストップ
	*/
	void Stop()
	{
		// ストップ状態では実行しない
		if (!m_stopped)
		{
			INT currTime;
			QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

			// ストップした時間を確保
			m_stopTime = currTime;
			m_stopped = true;
		}
	}

	/**
	* @brief 時計
	*/
	void Tick()
	{
		if (m_stopped)
		{
			m_deltaTime = 0.0;
			return;
		}

		INT64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		m_currTime = currTime;

		// 今のフレームと前フレームの差分
		m_deltaTime = (m_currTime - m_prevTime)*m_secondsPerCount;

		// 次のフレームの時間計算
		m_prevTime = m_currTime;

		// マイナスでないことを確認
		if (m_deltaTime < 0.0)
		{
			m_deltaTime = 0.0;
		}
	}

private:
	DOUBLE						m_secondsPerCount = 0.0;
	DOUBLE						m_deltaTime = -1.0;

	INT64						m_baseTime = 0;
	INT64						m_pausedTime = 0;
	INT64						m_stopTime = 0;
	INT64						m_prevTime = 0;
	INT64						m_currTime = 0;

	bool						m_stopped = false;
};

#endif