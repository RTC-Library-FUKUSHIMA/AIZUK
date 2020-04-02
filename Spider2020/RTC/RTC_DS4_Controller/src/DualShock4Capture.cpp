// -*- C++ -*-
/*!
 * @file DualShock4Capture.cpp
 * @brief DualShock4コントローラのキー入力の取得クラス
 * @author C.Saito
 * @date 2019/04/04
 */

#include "DualShock4Capture.h"
#include <algorithm>
#include <dirent.h>
#include <fcntl.h>
#include <iostream>
#include <linux/joystick.h>
#include <sys/stat.h>
#include <unistd.h>

/*! @name キーマップ
 *	DualShock4コントローラの各キーの固有ID
 */
/* @{ */
#define KEYMAP_AXIS_LX				(0)		/*!< 左スティック(左右)	*/
#define KEYMAP_AXIS_LY				(1)		/*!< 左スティック(上下)	*/
#define KEYMAP_AXIS_RX				(2)		/*!< 右スティック(左右)	*/
#define KEYMAP_AXIS_L2				(3)		/*!< L2ボタン			*/
#define KEYMAP_AXIS_R2				(4)		/*!< R2ボタン			*/
#define KEYMAP_AXIS_RY				(5)		/*!< 右スティック(上下)	*/
#define KEYMAP_AXIS_DIR_X			(16)	/*!< 十字ボタン(左右)	*/
#define KEYMAP_AXIS_DIR_Y			(17)	/*!< 十字ボタン(上下)	*/
#define KEYMAP_BUTTON_SQUARE		(304)	/*!< SQUAREボタン		*/
#define KEYMAP_BUTTON_CROSS			(305)	/*!< CROSSボタン		*/
#define KEYMAP_BUTTON_CIRCLE		(306)	/*!< CIRCLEボタン		*/
#define KEYMAP_BUTTON_TRIANGLE		(307)	/*!< TRIANGLEボタン		*/
#define KEYMAP_BUTTON_L1			(308)	/*!< L1ボタン			*/
#define KEYMAP_BUTTON_R1			(309)	/*!< R1ボタン			*/
#define KEYMAP_BUTTON_L2			(310)	/*!< L2ボタン			*/
#define KEYMAP_BUTTON_R2			(311)	/*!< R2ボタン			*/
#define KEYMAP_BUTTON_SHARE			(312)	/*!< SHAREボタン		*/
#define KEYMAP_BUTTON_OPTIONS		(313)	/*!< OPTIONSボタン		*/
#define KEYMAP_BUTTON_L3			(314)	/*!< L3ボタン			*/
#define KEYMAP_BUTTON_R3			(315)	/*!< R3ボタン			*/
#define KEYMAP_BUTTON_PS			(316)	/*!< PSボタン			*/
#define KEYMAP_BUTTON_TOUCH			(317)	/*!< TOUCHボタン		*/
/* @} */

/*! @name スレッド
 *	スレッドの制御
 */
/* @{ */
#define DEVICE_WAIT_TIME			(100000) 	/*!< デバイス接続待ち時間(us)	*/
#define THREAD_SLEEP_TIME			(500)		/*!< スレッドの休止時間(us)		*/
/* @} */

/*! @name バッテリ
 *	バッテリ残容量比の取得
 */
/* @{ */
#define POWER_SUPPLY_DIR 	("/sys/class/power_supply/")	/*!< 電源情報ディレクトリ				*/
#define DUALSHOCK4_PREFIX 	("sony_controller_battery")		/*!< バッテリ情報ディレクトリの接頭語	*/
#define CAPACITY_ID			("capacity")					/*!< バッテリ残容量比名				*/
/* @} */

DualShock4Capture::DualShock4Capture()
	: m_fdJoystick(-1)
	, m_fdCapacityRatio(-1)
	, m_bExitThread(true)
	, m_uAxisNumber(0)
	, m_uButtonNumber(0)
	, m_uCapacityRatio(0xFF)
{
}

DualShock4Capture::~DualShock4Capture()
{
	// キー入力に関するリソースを解放する
	InitKeyResource();
}

bool DualShock4Capture::Start(const std::string &sDeviceName)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	// 多重実行を防止する
	if((m_fdJoystick != -1) || (m_fdCapacityRatio != -1) || (m_spThread.get() != nullptr))
	{
		return false;
	}

	do
	{
		// デバイス名を更新する
		m_sDeviceName = sDeviceName;

		// デバイスを開く
		m_fdJoystick = open(sDeviceName.c_str(), O_RDONLY);
		if(m_fdJoystick == -1)
		{
			printf("open(%s) is failed\n", sDeviceName.c_str());
			break;
		}

		// バッテリ残容量比名を取得する
		m_sCapacityRatioName = GetCapacityRatioName();
		if(m_sCapacityRatioName.length() == 0)
		{
			printf("capacity ratio name is not existed\n");
			break;
		}

		// バッテリ残容量比を開く
		m_fdCapacityRatio = open(m_sCapacityRatioName.c_str(), O_RDONLY);
		if(m_fdCapacityRatio == -1)
		{
			printf("open(%s) is failed\n", m_sCapacityRatioName.c_str());
			break;
		}

		// デバイスの情報が安定するのを待つ
		std::this_thread::sleep_for(std::chrono::microseconds(DEVICE_WAIT_TIME));

		// デバイスの読み取りを非ブロッキングモードに設定する
		fcntl(m_fdJoystick, F_SETFL, O_NONBLOCK);

		// バッテリ残量比の読み取りを非ブロッキングモードに設定する
		fcntl(m_fdCapacityRatio, F_SETFL, O_NONBLOCK);

		// 識別子を取得する
		m_sId.resize(256, 0);
		ioctl(m_fdJoystick, JSIOCGNAME(m_sId.size()), m_sId.c_str());

		// 軸キーの数を取得する
		ioctl(m_fdJoystick, JSIOCGAXES, &m_uAxisNumber);

		// 軸キーのキーマッピングを取得する
		m_vecAxisKeyMap.resize(ABS_CNT, 0);
		ioctl(m_fdJoystick, JSIOCGAXMAP, &m_vecAxisKeyMap[0]);
		m_vecAxisKeyMap.resize(m_uAxisNumber);

		// 軸キーの入力具合のコンテナサイズを調整する
		m_vecAxisValue.resize(m_uAxisNumber, 0);

		// ボタンの数を取得する
		ioctl(m_fdJoystick, JSIOCGBUTTONS, &m_uButtonNumber);

		// ボタンのキーマッピングを取得する
		m_vecButtonKeyMap.resize(KEY_MAX - BTN_MISC + 1, 0);
		ioctl(m_fdJoystick, JSIOCGBTNMAP, &m_vecButtonKeyMap[0]);
		m_vecButtonKeyMap.resize(m_uButtonNumber);

		// ボタンの入力具合のコンテナサイズを調整する
		m_vecButtonValue.resize(m_uButtonNumber, 0);

		// 軸キーの入力具合及びボタンの押下状態を更新する
		UpdateKeyInfo();

		// バッテリ残容量比を更新する
		UpdateCapacityRatio();

		// スレッド終了フラグをOFFする
		m_bExitThread = false;

		// キー入力の状態の更新スレッドを生成する
		m_spThread.reset(new std::thread(&DualShock4Capture::Run, this));
		if(m_spThread.get() == nullptr)
		{
			printf("create thread is failed\n");
			break;
		}

		return true;
	}
	while(0);

	// キー入力に関するリソースを解放する
	InitKeyResource();

	return false;
}

void DualShock4Capture::Stop(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	// スレッド終了フラグをONする
	m_bExitThread = true;

	// 更新スレッドを停止する
	if(m_spThread.get() != nullptr)
	{
		{
			m_Mutex.unlock();

			// スレッド終了を待つ
			m_spThread->join();

			m_Mutex.lock();
		}

		// スレッドを破棄する
		m_spThread.release();
	}

	// キー入力に関するリソースを解放する
	InitKeyResource();
}

bool DualShock4Capture::IsValid(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	struct stat stJoystick = {0};
	struct stat stCapacityRatio = {0};
	int iRetJoystick = 0;
	int iRetCapacityRatio = 0;

	// デバイスの状態を取得する
	iRetJoystick = stat(m_sDeviceName.c_str(), &stJoystick);

	// バッテリ残容量比の状態を取得する
	iRetCapacityRatio = stat(m_sCapacityRatioName.c_str(), &stCapacityRatio);

	return (((iRetJoystick != -1) && (m_fdJoystick != -1)) && ((iRetCapacityRatio != -1) && (m_fdCapacityRatio != -1)));
}

std::string DualShock4Capture::GetDeviceName(void)
{
   std::lock_guard<std::recursive_mutex> lock(m_Mutex);

   return m_sDeviceName;
}

std::string DualShock4Capture::GetId(void)
{
   std::lock_guard<std::recursive_mutex> lock(m_Mutex);

   return m_sId;
}

 uint8_t DualShock4Capture::GetAxisNumber(void)
 {
 	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

 	return m_uAxisNumber;
 }

 uint8_t DualShock4Capture::GetButtonNumber(void)
 {
 	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

 	return m_uButtonNumber;
 }

int16_t DualShock4Capture::GetDirHorizontalAxisValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetAxisValue(KEYMAP_AXIS_DIR_X, 0);
}

int16_t DualShock4Capture::GetDirVerticalAxisValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetAxisValue(KEYMAP_AXIS_DIR_Y, 0);
}

int16_t DualShock4Capture::GetLStickHorizontalAxisValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetAxisValue(KEYMAP_AXIS_LX, 0);
}

int16_t DualShock4Capture::GetLStickVerticalAxisValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetAxisValue(KEYMAP_AXIS_LY, 0);
}

int16_t DualShock4Capture::GetRStickHorizontalAxisValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetAxisValue(KEYMAP_AXIS_RX, 0);
}

int16_t DualShock4Capture::GetRStickVerticalAxisValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetAxisValue(KEYMAP_AXIS_RY, 0);
}

int16_t DualShock4Capture::GetL2AxisValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetAxisValue(KEYMAP_AXIS_L2, -32767);
}

int16_t DualShock4Capture::GetR2AxisValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetAxisValue(KEYMAP_AXIS_R2, -32767);
}

int16_t DualShock4Capture::GetSquareButtonValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetButtonValue(KEYMAP_BUTTON_SQUARE, 0);
}

int16_t DualShock4Capture::GetCrossButtonValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetButtonValue(KEYMAP_BUTTON_CROSS, 0);
}

int16_t DualShock4Capture::GetCircleButtonValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetButtonValue(KEYMAP_BUTTON_CIRCLE, 0);
}

int16_t DualShock4Capture::GetTriangleButtonValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetButtonValue(KEYMAP_BUTTON_TRIANGLE, 0);
}

int16_t DualShock4Capture::GetL1ButtonValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetButtonValue(KEYMAP_BUTTON_L1, 0);
}

int16_t DualShock4Capture::GetR1ButtonValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetButtonValue(KEYMAP_BUTTON_R1, 0);
}

int16_t DualShock4Capture::GetL2ButtonValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetButtonValue(KEYMAP_BUTTON_L2, 0);
}

int16_t DualShock4Capture::GetR2ButtonValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetButtonValue(KEYMAP_BUTTON_R2, 0);
}

int16_t DualShock4Capture::GetShareButtonValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetButtonValue(KEYMAP_BUTTON_SHARE, 0);
}

int16_t DualShock4Capture::GetOptionsButtonValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetButtonValue(KEYMAP_BUTTON_OPTIONS, 0);
}

int16_t DualShock4Capture::GetL3ButtonValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetButtonValue(KEYMAP_BUTTON_L3, 0);
}

int16_t DualShock4Capture::GetR3ButtonValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetButtonValue(KEYMAP_BUTTON_R3, 0);
}

int16_t DualShock4Capture::GetPSButtonValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetButtonValue(KEYMAP_BUTTON_PS, 0);
}

int16_t DualShock4Capture::GetTouchButtonValue(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	return GetButtonValue(KEYMAP_BUTTON_TOUCH, 0);
}

uint8_t DualShock4Capture::GetCapacityRatio(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	// 情報取得の可否をチェックする
	if(!IsValid())
	{
		return 0xFF;
	}

	return m_uCapacityRatio;
}

void DualShock4Capture::Run(void)
{
	while(1)
	{
		{
			std::lock_guard<std::recursive_mutex> lock(m_Mutex);

			// スレッド終了フラグがONならループから抜ける
			if(m_bExitThread)
			{
				break;
			}

			// 情報取得の可否をチェックする
			if(!IsValid())
			{
				// リソースを解放する(切断対策)
				InitKeyResource();
				break;
			}

			// 軸キーの入力具合及びボタンの押下状態を更新する
			UpdateKeyInfo();

			// バッテリの残容量比を更新する
			UpdateCapacityRatio();
		}

		// スレッドを休止する
		std::this_thread::sleep_for(std::chrono::microseconds(THREAD_SLEEP_TIME));
	}
}

void DualShock4Capture::InitKeyResource(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	// デバイスを閉じる
	if(m_fdJoystick != -1)
	{
		close(m_fdJoystick);
		m_fdJoystick = -1;
	}

	// バッテリ残容量比名を閉じる
	if(m_fdCapacityRatio != -1)
	{
		close(m_fdCapacityRatio);
		m_fdCapacityRatio = -1;
	}

	// デバイス名を初期化する
	m_sDeviceName.clear();

	// 識別子を初期化する
	m_sId.clear();

	// 軸キーの数を初期化する
	m_uAxisNumber = 0;

	// 軸キーのキーマッピングを初期化する
	m_vecAxisKeyMap.clear();

	// 軸キーの入力具合のコンテナサイズを初期化する
	m_vecAxisValue.clear();

	// ボタンの数を初期化する
	m_uButtonNumber = 0;

	// ボタンのキーマッピングを初期化する
	m_vecButtonKeyMap.clear();

	// ボタンの入力具合のコンテナサイズを初期化する
	m_vecButtonValue.clear();

	// バッテリ残容量比名を初期化する
	m_sCapacityRatioName.clear();

	// バッテリ残存容量比を初期化する
	m_uCapacityRatio = 0xFF;
}

void DualShock4Capture::UpdateKeyInfo(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	struct js_event event = {0};
	ssize_t sizeRet = 0;

	// 情報取得の可否をチェックする
	if(!IsValid())
	{
		return;
	}

	while(1)
	{
		// キー入力の情報を読み込む
		sizeRet = read(m_fdJoystick, &event, sizeof(event));
		if(sizeRet != sizeof(event))
		{
			break;
		}

		// 軸キーまたはボタンの入力の情報なら更新する
		switch(event.type & (JS_EVENT_BUTTON|JS_EVENT_AXIS))
		{
		case JS_EVENT_AXIS:
			if(event.number < m_vecAxisValue.size())
			{
				m_vecAxisValue[event.number] = event.value;
			}
			break;
		case JS_EVENT_BUTTON:
			if(event.number < m_vecButtonValue.size())
			{
				m_vecButtonValue[event.number] = event.value;
			}
			break;
		default:
			break;
		}
	}
}

void DualShock4Capture::UpdateCapacityRatio(void)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	char sCapacityData[4] = {0};
	ssize_t sizeRet = 0;
	int i = 0;

	// 情報取得の可否をチェックする
	if(!IsValid())
	{
		return;
	}

	// ファイルのオフセットを先頭に設定する
	lseek(m_fdCapacityRatio, 0, SEEK_SET);

	// バッテリ残容量比を読み込む
	sizeRet = read(m_fdCapacityRatio, sCapacityData, sizeof(sCapacityData) - 1);
	if(0 < sizeRet)
	{
		// 文字列に非数値があればNUL文字に置き換える
		for(i = 0; i < std::string(sCapacityData).length(); i++)
		{
			if(!isdigit(sCapacityData[i]))
			{
				sCapacityData[i] = 0;
				break;
			}
		}

		// 数値文字列を数値に変換する
		if(0 < i)
		{
			m_uCapacityRatio = atoi(sCapacityData);
		}
	}
}

int16_t DualShock4Capture::GetAxisValue(uint8_t uiKeyMap, int16_t iDefaultValue)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	size_t sizeIndex = 0;

	// キー入力の取得の可否をチェックする
	if(!IsValid())
	{
		return iDefaultValue;
	}

	// ボタンのキーマップを検索する
	sizeIndex = std::distance(m_vecAxisKeyMap.begin(), std::find(m_vecAxisKeyMap.begin(), m_vecAxisKeyMap.end(), uiKeyMap));

	// 検索の成否をチェックする
	if((m_vecAxisKeyMap.size() <= sizeIndex) || (m_vecAxisValue.size() <= sizeIndex))
	{
		return iDefaultValue;
	}

	return m_vecAxisValue[sizeIndex];
}

int16_t DualShock4Capture::GetRawAxisValue(uint8_t uiKeyMap, int16_t iDefaultValue)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	size_t sizeIndex = 0;

	// ボタンのキーマップを検索する
	sizeIndex = std::distance(m_vecAxisKeyMap.begin(), std::find(m_vecAxisKeyMap.begin(), m_vecAxisKeyMap.end(), uiKeyMap));

	// 検索の成否をチェックする
	if((m_vecAxisKeyMap.size() <= sizeIndex) || (m_vecAxisValue.size() <= sizeIndex))
	{
		return iDefaultValue;
	}

	return m_vecAxisValue[sizeIndex];
}

int16_t DualShock4Capture::GetButtonValue(uint16_t uiKeyMap, int16_t iDefaultValue)
{
	std::lock_guard<std::recursive_mutex> lock(m_Mutex);

	size_t sizeIndex = 0;

	// キー入力の取得の可否をチェックする
	if(!IsValid())
	{
		return iDefaultValue;
	}

	// ボタンのキーマップを検索する
	sizeIndex = std::distance(m_vecButtonKeyMap.begin(), std::find(m_vecButtonKeyMap.begin(), m_vecButtonKeyMap.end(), uiKeyMap));

	// 検索の成否をチェックする
	if((m_vecButtonKeyMap.size() <= sizeIndex) || (m_vecButtonValue.size() <= sizeIndex))
	{
		return iDefaultValue;
	}

	return m_vecButtonValue[sizeIndex];
}

std::string DualShock4Capture::GetCapacityRatioName(void)
{
	DIR *dp = nullptr;
	struct dirent *dent = nullptr;
	std::string sCapacityRatioName;

	// 電源情報の格納ディレクトリをオープンする
	dp = opendir(POWER_SUPPLY_DIR);
	if(dp != nullptr)
	{
		do
		{
			// ディレクトリのエントリーを読み込む
			dent = readdir(dp);
			if(dent == nullptr)
			{
				break;
			}

			// DualShock4コントローラのエントリーを検索する
			if(std::string(dent->d_name).compare(0, std::string(DUALSHOCK4_PREFIX).length(), DUALSHOCK4_PREFIX) == 0)
			{
				// DualShock4コントローラのバッテリ残量比名を生成する
				sCapacityRatioName += POWER_SUPPLY_DIR;
				sCapacityRatioName += dent->d_name;
				sCapacityRatioName += "/";
				sCapacityRatioName += CAPACITY_ID;
				break;
			}
		}
		while(1);

		// 電源情報の格納ディレクトリをクローズする
		closedir(dp);
		dp = nullptr;
	}

	return sCapacityRatioName;
}
