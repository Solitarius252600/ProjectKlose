/**
* @file Timer.h
* @brief �^�C�}�[�N���X
* @author EtuCho
* @date 2019/04/14
* @details FPS�v�Z�ƃA�v���P�[�V�������s���ԗp�N���X�A�ǂݍ��݉񐔏��Ȃ����߃��\�b�h�͊�{�C�����C���W�J
*/


#ifndef INCLUDE_D2D1TIMER
#define INCLUDE_D2D1TIMER

#include <sstream>
#include "Common.h"

/**
* @brief �^�C�����v��N���X
* @details FPS�v�Z��DeltaTime�v�Z
*/
class D3D11Timer
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	D3D11Timer()
	{
		INT64 countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		m_secondsPerCount = 1.0 / (double)countsPerSec;
	}

	/**
	* @brief �g�[�^���^�C��
	*/
	float TotalTime() const
	{
		if (m_stopped)
			return (float)(((m_stopTime - m_pausedTime) - m_baseTime)*m_secondsPerCount);
		else
			return (float)(((m_currTime - m_pausedTime) - m_baseTime)*m_secondsPerCount);
	}

	/**
	* @brief �f���^�^�C��
	*/
	float DeltaTime() const { return (float)m_deltaTime; }

	/**
	* @brief ���[�v����O�Ɉ�񃊃Z�b�g
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
	* @brief �X�^�[�g
	*/
	void Start()
	{
		INT startTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

		// �X�g�b�v��ԂȂ���s
		if (m_stopped)
		{
			// �~�܂��Ă鎞�Ԃ��v��
			m_pausedTime += (startTime - m_stopTime);
			// ��񃊃Z�b�g
			m_prevTime = startTime;
			// �X�g�b�v����
			m_stopTime = 0;
			m_stopped = false;
		}
	}

	/**
	* @brief �X�g�b�v
	*/
	void Stop()
	{
		// �X�g�b�v��Ԃł͎��s���Ȃ�
		if (!m_stopped)
		{
			INT currTime;
			QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

			// �X�g�b�v�������Ԃ��m��
			m_stopTime = currTime;
			m_stopped = true;
		}
	}

	/**
	* @brief ���v
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

		// ���̃t���[���ƑO�t���[���̍���
		m_deltaTime = (m_currTime - m_prevTime)*m_secondsPerCount;

		// ���̃t���[���̎��Ԍv�Z
		m_prevTime = m_currTime;

		// �}�C�i�X�łȂ����Ƃ��m�F
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