/*!
 * @file FingerDeltaWrapper.h
 * @brief Jaco2アームの指の開閉具合の変位速度入出力のラッパークラス
 * @author C.Saito
 * @date 2019/04/18
 */

#ifndef FINGER_DELTA_WRAPPER_H
#define FINGER_DELTA_WRAPPER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <cstdint>

/*!
 * Jaco2アームの指の開閉具合の変位速度入出力のラッパークラス
 */
class FingerDeltaWrapper
{
public:
	/*!
	 * コンストラクタ
	 * @method FingerDeltaWrapper
	 * @param  Port   ラッピングする変数
	 */
	FingerDeltaWrapper(RTC::TimedLongSeq& Port);

	/*!
	 * デストラクタ
	 * @method FingerDeltaWrapper
	 */
	virtual ~FingerDeltaWrapper();

	/*!
	 * 代入演算子のオーバーロード
	 * @method operator=
	 */
	FingerDeltaWrapper& operator=(const FingerDeltaWrapper& rhs);

	/*!
	 * タイムスタンプを設定する
	 * @method SetTimestamp
	 * @return なし
	 */
	void SetTimestamp(void);

	/*!
	 * Jaco2アームの指の開閉具合の変位速度の入出力の配列数と値を初期化する
	 * @method InitData
	 * @return なし
	 */
	void InitData(void);

	/*!
	 * Jaco2アームの指の開閉具合の変位速度の数を取得する
	 * @method GetNumber
	 * @return データの数
	 */
	 uint8_t GetNumber(void);

	/*!
	 * Jaco2アームの親指の開閉具合の変位速度を取得する
	 * @method GetThumbDelta(void)
	 * @return 指の開閉具合の変位速度
	 */
	int32_t GetThumbDelta(void);

	/*!
	 * Jaco2アームの親指の開閉具合の変位速度を設定する
	 * @method SetThumbDelta
	 * @param  iValue   指の開閉具合の変位速度
	 * @return なし
	 */
	void SetThumbDelta(const int32_t iValue);

	/*!
	 * Jaco2アームの差指の開閉具合の変位速度を取得する
	 * @method GetIndexFingerDelta(void)
	 * @return 指の開閉具合の変位速度
	 */
	int32_t GetIndexFingerDelta(void);

	/*!
	 * Jaco2アームの親指の開閉具合の変位速度を設定する
	 * @method SetIndexFingerDelta
	 * @param  iValue   指の開閉具合の変位速度
	 * @return なし
	 */
	void SetIndexFingerDelta(const int32_t iValue);

	/*!
	 * Jaco2アームの中指の開閉具合の変位速度を取得する
	 * @method GetMiddleFingerDelta(void)
	 * @return 指の開閉具合の変位速度
	 */
	int32_t GetMiddleFingerDelta(void);

	/*!
	 * Jaco2アームの中指の開閉具合の変位速度を設定する
	 * @method SetMiddleFingerDelta
	 * @param  iValue   指の開閉具合の変位速度
	 * @return なし
	 */
	void SetMiddleFingerDelta(const int32_t iValue);

private:
	RTC::TimedLongSeq& m_Port;	/*!< ラッピングする変数の参照変数	*/
};

#endif//FINGER_DELTA_WRAPPER_H
