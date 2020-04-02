/*!
 * @file FingerStatusWrapper.h
 * @brief Jaco2アームの指の開閉具合の入出力のラッパークラス
 * @author C.Saito
 * @date 2019/12/27
 */

#ifndef FINGER_STATUS_WRAPPER_H
#define FINGER_STATUS_WRAPPER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <cstdint>

/*!
 * Jaco2アームの指の開閉具合の入出力のラッパークラス
 * @details 次のlong型配列で提供するデータの操作APIを提供する
 *          [0]: Thumbの開閉具合
 *          [1]: Index Fingerの開閉具合
 *          [2]: Middle Fingerの開閉具合
 */
class FingerStatusWrapper
{
public:
	/*!
	 * コンストラクタ
	 * @method FingerStatusWrapper
	 * @param  Port   ラッピングする変数
	 */
	FingerStatusWrapper(RTC::TimedLongSeq& Port);

	/*!
	 * デストラクタ
	 * @method FingerStatusWrapper
	 */
	virtual ~FingerStatusWrapper();

	/*!
	 * 代入演算子のオーバーロード
	 * @method operator=
	 */
	FingerStatusWrapper& operator=(const FingerStatusWrapper& rhs);

	/*!
	 * タイムスタンプを設定する
	 * @method SetTimestamp
	 * @return なし
	 */
	void SetTimestamp(void);

	/*!
	 * Jaco2アームの指の開閉具合の入出力の配列数と値を初期化する
	 * @method InitData
	 * @return なし
	 */
	void InitData(void);

	/*!
	 * Jaco2アームの指の開閉具合の数を取得する
	 * @method GetNumber
	 * @return データの数
	 */
	 uint8_t GetNumber(void);

	/*!
	 * Jaco2アームの親指の開閉具合を取得する
	 * @method GetThumbStatus(void)
	 * @return 親指の開閉具合
	 */
	int32_t GetThumbStatus(void);

	/*!
	 * Jaco2アームの親指の開閉具合を設定する
	 * @method SetThumbStatus
	 * @param  iValue   指の開閉具合の変位速度
	 * @return なし
	 */
	void SetThumbStatus(const int32_t iValue);

	/*!
	 * Jaco2アームの差指の開閉具合を取得する
	 * @method GetIndexFingerStatus(void)
	 * @return 差指の開閉具合
	 */
	int32_t GetIndexFingerStatus(void);

	/*!
	 * Jaco2アームの親指の開閉具合を設定する
	 * @method SetIndexFingerStatus
	 * @param  iValue   差指の開閉具合
	 * @return なし
	 */
	void SetIndexFingerStatus(const int32_t iValue);

	/*!
	 * Jaco2アームの中指の開閉具合を取得する
	 * @method GetMiddleFingerStatus(void)
	 * @return 中指の開閉具合
	 */
	int32_t GetMiddleFingerStatus(void);

	/*!
	 * Jaco2アームの中指の開閉具合を設定する
	 * @method SetMiddleFingerStatus
	 * @param  iValue   中指の開閉具合
	 * @return なし
	 */
	void SetMiddleFingerStatus(const int32_t iValue);

private:
	RTC::TimedLongSeq& m_Port;	/*!< ラッピングする変数の参照変数	*/
};

#endif//FINGER_STATUS_WRAPPER_H
