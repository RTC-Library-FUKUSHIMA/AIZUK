/*!
 * @file FlipperPwmWrapper.h
 * @brief フリッパーのPWM指令入出力のラッパークラス
 * @author C.Saito
 * @date 2019/04/18
 */

#ifndef FLIPPER_PWM_WRAPPER_H
#define FLIPPER_PWM_WRAPPER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <cstdint>

/*!
 * @brief フリッパーのPWM指令入出力のラッパークラス
 * @details 次のdouble型配列で提供するデータの操作APIを提供する
 *          [0]: 右前方フリッパーのPWM指令
 *          [1]: 左前方フリッパーのPWM指令
 *          [2]: 右後方フリッパーのPWM指令
 *          [3]: 左後方フリッパーのPWM指令
 */
class FlipperPwmWrapper
{
public:
	/*!
	 * コンストラクタ
	 * @method FlipperPwmWrapper
	 * @param  Port   ラッピングする変数
	 */
	FlipperPwmWrapper(RTC::TimedLongSeq& Port);

	/*!
	 * デストラクタ
	 * @method FlipperPwmWrapper
	 */
	virtual ~FlipperPwmWrapper();

	/*!
	 * 代入演算子のオーバーロード
	 * @method operator=
	 */
	FlipperPwmWrapper& operator=(const FlipperPwmWrapper& rhs);

	/*!
	 * タイムスタンプを設定する
	 * @method SetTimestamp
	 * @return なし
	 */
	void SetTimestamp(void);

	/*!
	 * フリッパーのPWM指令の入出力の配列数と値を初期化する
	 * @method InitData
	 * @return なし
	 */
	void InitData(void);

	/*!
	 * フリッパーのPWM指令の数を取得する
	 * @method GetNumber
	 * @return データの数
	 */
	 uint8_t GetNumber(void);

	/*!
	 * 右前方フリッパーのPWM指令を取得する
	 * @method GetFrontRightPwm
	 * @return フリッパーのPWM指令
	 */
	int32_t GetFrontRightPwm(void);

	/*!
	 * 右前方フリッパーのPWM指令を設定する
	 * @method SetFrontRightPwm
	 * @param  iValue   フリッパーのPWM指令
	 * @return なし
	 */
	void SetFrontRightPwm(const int32_t iValue);

	/*!
	 * 左前方フリッパーのPWM指令を取得する
	 * @method GetFrontLeftPwm
	 * @return フリッパーのPWM指令
	 */
	int32_t GetFrontLeftPwm(void);

	/*!
	 * 左前方フリッパーのPWM指令を設定する
	 * @method SetFrontLeftPwm
	 * @param  iValue   フリッパーのPWM指令
	 * @return なし
	 */
	void SetFrontLeftPwm(const int32_t iValue);

	/*!
	 * 右後方フリッパーのPWM指令を取得する
	 * @method GetBackRightPwm
	 * @return フリッパーのPWM指令
	 */
	int32_t GetBackRightPwm(void);

	/*!
	 * 右後方フリッパーのPWM指令を設定する
	 * @method SetBackRightPwm
	 * @param  iValue   フリッパーのPWM指令
	 * @return なし
	 */
	void SetBackRightPwm(const int32_t iValue);

	/*!
	 * 左前方フリッパーのPWM指令を取得する
	 * @method GetBackLeftPwm
	 * @return フリッパーのPWM指令
	 */
	int32_t GetBackLeftPwm(void);

	/*!
	 * 左前方フリッパーのPWM指令を設定する
	 * @method SetBackLeftPwm
	 * @param  iValue   フリッパーのPWM指令
	 * @return なし
	 */
	void SetBackLeftPwm(const int32_t iValue);

private:
	RTC::TimedLongSeq& m_Port;	/*!< ラッピングする変数の参照変数	*/
};

#endif//FLIPPER_PWM_WRAPPER_H
