// -*- C++ -*-
/*!
 * @file DualShock4Capture.h
 * @brief DualShock4コントローラのキー入力の取得クラス
 * @author C.Saito
 * @date 2019/04/04
 */

#ifndef DUALSHOCK4_CAPTURE_H
#define DUALSHOCK4_CAPTURE_H

#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

/*!
 * DualShock4コントローラのキー入力の取得クラス
 */
class DualShock4Capture
{
public:
	/*!
	 * コンストラクタ
	 * @method DualShock4Capture
	 */
	DualShock4Capture();

	/*!
	 * デストラクタ
	 * @method ~DualShock4Capture
	 */
	virtual ~DualShock4Capture();

	/*!
	 * キー入力の取得処理を開始する
	 * @method Start
	 * @param  sDeviceName デバイス名
	 * @retval true キー入力の取得処理の開始に成功した
	 * @retval false キー入力の取得処理の開始に失敗した
	 */
	bool Start(const std::string &sDeviceName);

	/*!
	 * キー入力の取得処理を終了する
	 * @method Stop
	 * @return なし
	 */
	void Stop(void);

	/*!
	 * 情報の取得の可否をチェックする
	 * @method IsValid
	 * @retval true キー入力の取得可
	 * @retval false キー入力の取得不可
	 */
	bool IsValid(void);

	/*!
	 * デバイス名を取得する
	 * @method GetDeviceName
	 * @return デバイス名
	 * @remark 情報取得不可の時、戻り値はNULL文字を返す
	 */
	std::string GetDeviceName(void);

	/*!
	 * 識別子を取得する
	 * @method GetId
	 * @return 識別子
	 * @remark 情報取得不可の時、戻り値はNULL文字を返す
	 */
	std::string GetId(void);

	/*!
	 * 軸キーの数を取得する
	 * @method GetAxisNumber
	 * @return 軸キーの数
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	 uint8_t GetAxisNumber(void);

	 /*!
 	 * ボタンの数を取得する
 	 * @method GetButtonNumber
 	 * @return ボタンの数
 	 * @remark 情報取得不可の時、戻り値は0を返す
 	 */
 	 uint8_t GetButtonNumber(void);

	 /*!
 	 * 十字ボタン(左右)の入力具合を取得する
 	 * @method GetDirHorizontalAxisValue
 	 * @return 押下具合(-32767〜32767)
 	 * @remark 情報取得不可の時、戻り値は0を返す
 	 */
 	int16_t GetDirHorizontalAxisValue(void);

	/*!
	 * 十字ボタン(上下)の入力具合を取得する
	 * @method GetDirVerticalAxisValue
	 * @return 押下具合(-32767〜32767)
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetDirVerticalAxisValue(void);

	/*!
	 * 左スティック(左右)の入力具合を取得する
	 * @method GetLStickHorizontalAxisValue
	 * @return 押下具合(-32767〜32767)
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetLStickHorizontalAxisValue(void);

	/*!
	 * 左スティック(上下)の入力具合を取得する
	 * @method GetLStickVerticalAxisValue
	 * @return 押下具合(-32767〜32767)
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetLStickVerticalAxisValue(void);

	/*!
	 * 右スティック(左右)の入力具合を取得する
	 * @method GetRStickHorizontalAxisValue
	 * @return 押下具合(-32767〜32767)
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetRStickHorizontalAxisValue(void);

	/*!
	 * 右スティック(上下)の入力具合を取得する
	 * @method GetRStickVerticalAxisValue
	 * @return 押下具合(-32767〜32767)
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetRStickVerticalAxisValue(void);

	/*!
	 * L2ボタンの入力具合を取得する
	 * @method GetL2AxisValue
	 * @return 押下具合(-32767〜32767)
	 * @remark 情報取得不可の時、戻り値は-32767を返す
	 */
	int16_t GetL2AxisValue(void);

	/*!
	 * R2ボタンの入力具合を取得する
	 * @method GetR2AxisValue
	 * @return 押下具合(-32767〜32767)
	 * @remark 情報取得不可の時、戻り値は-32767を返す
	 */
	int16_t GetR2AxisValue(void);

	/*!
	 * SQUAREボタンの押下状態を取得する
	 * @method GetSquareButtonValue
	 * @retval 0 非押下
	 * @retval 1 押下
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetSquareButtonValue(void);

	/*!
	 * CROSSボタンの押下状態を取得する
	 * @method GetCrossButtonValue
	 * @retval 0 非押下
	 * @retval 1 押下
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetCrossButtonValue(void);

	/*!
	 * CIRCLEボタンの押下状態を取得する
	 * @method GetCircleButtonValue
	 * @retval 0 非押下
	 * @retval 1 押下
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetCircleButtonValue(void);

	/*!
	 * TRIANGLEボタンの押下状態を取得する
	 * @method GetTriangleButtonValue
	 * @retval 0 非押下
	 * @retval 1 押下
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetTriangleButtonValue(void);

	/*!
	 * L1ボタンの押下状態を取得する
	 * @method GetL1ButtonValue
	 * @retval 0 非押下
	 * @retval 1 押下
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetL1ButtonValue(void);

	/*!
	 * R1ボタンの押下状態を取得する
	 * @method GetR1ButtonValue
	 * @retval 0 非押下
	 * @retval 1 押下
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetR1ButtonValue(void);

	/*!
	 * L2ボタンの押下状態を取得する
	 * @method GetL2ButtonValue
	 * @retval 0 非押下
	 * @retval 1 押下
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetL2ButtonValue(void);

	/*!
	 * R2ボタンの押下状態を取得する
	 * @method GetR2ButtonValue
	 * @retval 0 非押下
	 * @retval 1 押下
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetR2ButtonValue(void);

	/*!
	 * SHAREボタンの押下状態を取得する
	 * @method GetShareButtonValue
	 * @retval 0 非押下
	 * @retval 1 押下
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetShareButtonValue(void);

	/*!
	 * OPTIONSボタンの押下状態を取得する
	 * @method GetOptionsButtonValue
	 * @retval 0 非押下
	 * @retval 1 押下
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetOptionsButtonValue(void);

	/*!
	 * L3ボタンの押下状態を取得する
	 * @method GetL3ButtonValue
	 * @retval 0 非押下
	 * @retval 1 押下
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetL3ButtonValue(void);

	/*!
	 * R3ボタンの押下状態を取得する
	 * @method GetR3ButtonValue
	 * @retval 0 非押下
	 * @retval 1 押下
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetR3ButtonValue(void);

	/*!
	 * PSボタンの押下状態を取得する
	 * @method GetPSButtonValue
	 * @retval 0 非押下
	 * @retval 1 押下
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetPSButtonValue(void);

	/*!
	 * TOUCHボタンの押下状態を取得する
	 * @method GetTouchButtonValue
	 * @retval 0 非押下
	 * @retval 1 押下
	 * @remark 情報取得不可の時、戻り値は0を返す
	 */
	int16_t GetTouchButtonValue(void);

	/*!
	 * バッテリ残存容量比を取得する
	 * @method GetCapacityRatio
	 * @retval 0〜100 取得成功
	 * @retval 255 取得失敗
	 */
	uint8_t GetCapacityRatio(void);

private:
	/*!
	 * キー入力の状態を更新する
	 * @method Run
	 * @return なし
	 */
	void Run(void);

	/*!
	 * キー入力(スレッド制御を除く)に関するリソースを解放する
	 * @method InitKeyResource
	 * @return なし
	 */
	void InitKeyResource(void);

	/*!
	* 軸キーの入力具合及びボタンの押下状態を更新する
	* @method UpdateKeyInfo
	* @return なし
	 */
	void UpdateKeyInfo(void);

	/*!
	* バッテリの残容量比を更新する
	* @method UpdateCapacityRatio
	* @return なし
	 */
	void UpdateCapacityRatio(void);

	/*!
	 * 軸キーの入力具合を取得する
	 * @method GetAxisValue
	 * @param  uiKeyMap       キーマップ
	 * @param  iDefaultValue  初期値
	 * @return 指定したキーマップに該当する軸キーの押下状態(0,1)
	 * @remark 情報取得不可または該当するボタンなしの時、戻り値は初期値を返す
	 */
	int16_t GetAxisValue(uint8_t uiKeyMap, int16_t iDefaultValue);

	/*!
	 * 軸キーの入力具合を取得する
	 * @method GetRawAxisValue
	 * @param  uiKeyMap       キーマップ
	 * @param  iDefaultValue  初期値
	 * @return 指定したキーマップに該当するボタンの入力具合(-32767〜32767)
	 * @remark 該当する軸キーなしの時、戻り値は初期値を返す
	 */
	int16_t GetRawAxisValue(uint8_t uiKeyMap, int16_t iDefaultValue);

	/*!
	 * ボタンの押下状態を取得する
	 * @method GetButtonValue
	 * @param  uiKeyMap       キーマップ
	 * @param  iDefaultValue  初期値
	 * @return 指定したキーマップに該当するボタンの押下状態(0,1)
	 * @remark 情報取得不可または該当するボタンなしの時、戻り値は初期値を返す
	 */
	int16_t GetButtonValue(uint16_t uiKeyMap, int16_t iDefaultValue);

	/*!
	 * バッテリ残容量比名を取得する
	 * @method GetCapacityRatioName
	 * @param  なし
	 * @remark 情報の取得不可の時、戻り値はNUL文字を返す
	 */
	std::string GetCapacityRatioName(void);

	int m_fdJoystick;							/*!< ジョイスティック用ファイルディスクリプタ	*/
	int m_fdCapacityRatio;						/*! バッテリ残容量比用ファイルディスクリプタ	*/
	std::unique_ptr<std::thread> m_spThread;	/*!< スレッドクラス								*/
	bool m_bExitThread;							/*!< スレッド終了フラグ							*/
	std::recursive_mutex m_Mutex;				/*!< 再帰ミューテックス							*/

	std::string m_sDeviceName;					/*!< デバイス名									*/
	std::string m_sId;							/*!< 識別子										*/
	uint8_t m_uAxisNumber; 						/*!< 軸キーの数									*/
	std::vector<uint8_t> m_vecAxisKeyMap;		/*!< 軸キーのキーマップのコンテナ				*/
	std::vector<int16_t> m_vecAxisValue;		/*!< 軸キーの入力具合のコンテナ					*/
	uint8_t m_uButtonNumber;					/*!< ボタンの数									*/
	std::vector<uint16_t> m_vecButtonKeyMap; 	/*!< ボタンのキーマップのコンテナ				*/
	std::vector<int16_t> m_vecButtonValue;		/*!< ボタンの押下状態のコンテナ					*/
	std::string m_sCapacityRatioName;			/*!< バッテリ残容量比名							*/
	uint8_t m_uCapacityRatio;					/*!< バッテリ残存容量比							*/
};

#endif//DUALSHOCK4_CAPTURE_H
