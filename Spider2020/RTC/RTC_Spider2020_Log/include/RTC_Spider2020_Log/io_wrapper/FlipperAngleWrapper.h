/*!
 * @file FlipperAngleWrapper.h
 * @brief フリッパーの角度入出力のラッパークラス
 * @author C.Saito
 * @date 2019/04/18
 */

#ifndef FLIPPER_ANGLE_WRAPPER_H
#define FLIPPER_ANGLE_WRAPPER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <cstdint>

/*!
 * @brief フリッパーの角度入出力のラッパークラス
 * @details 次のdouble型配列で提供するデータの操作APIを提供する
 *          [0]: 右前方フリッパーの角度
 *          [1]: 左前方フリッパーの角度
 *          [2]: 右後方フリッパーの角度
 *          [3]: 左後方フリッパーの角度
 */
class FlipperAngleWrapper
{
public:
	/*!
	 * コンストラクタ
	 * @method FlipperAngleWrapper
	 * @param  Port   ラッピングする変数
	 */
	FlipperAngleWrapper(RTC::TimedDoubleSeq& Port);

	/*!
	 * デストラクタ
	 * @method FlipperAngleWrapper
	 */
	virtual ~FlipperAngleWrapper();

	/*!
	 * 代入演算子のオーバーロード
	 * @method operator=
	 */
	FlipperAngleWrapper& operator=(const FlipperAngleWrapper& rhs);

	/*!
	 * タイムスタンプを設定する
	 * @method SetTimestamp
	 * @return なし
	 */
	void SetTimestamp(void);

	/*!
	 * フリッパーの角度の入出力の配列数と値を初期化する
	 * @method InitData
	 * @return なし
	 */
	void InitData(void);

	/*!
	 * フリッパーの角度の数を取得する
	 * @method GetNumber
	 * @return データの数
	 */
	 uint8_t GetNumber(void);

	/*!
	 * 右前方フリッパーの角度を取得する
	 * @method GetFrontRightAngle
	 * @return フリッパーの角度
	 */
	double GetFrontRightAngle(void);

	/*!
	 * 右前方フリッパーの角度を設定する
	 * @method SetFrontRightAngle
	 * @param  iValue   フリッパーの角度
	 * @return なし
	 */
	void SetFrontRightAngle(const double iValue);

	/*!
	 * 左前方フリッパーの角度を取得する
	 * @method GetFrontLeftAngle
	 * @return フリッパーの角度
	 */
	double GetFrontLeftAngle(void);

	/*!
	 * 左前方フリッパーの角度を設定する
	 * @method SetFrontLeftAngle
	 * @param  iValue   フリッパーの角度
	 * @return なし
	 */
	void SetFrontLeftAngle(const double iValue);

	/*!
	 * 右後方フリッパーの角度を取得する
	 * @method GetBackRightAngle
	 * @return フリッパーの角度
	 */
	double GetBackRightAngle(void);

	/*!
	 * 右後方フリッパーの角度を設定する
	 * @method SetBackRightAngle
	 * @param  iValue   フリッパーの角度
	 * @return なし
	 */
	void SetBackRightAngle(const double iValue);

	/*!
	 * 左前方フリッパーの角度を取得する
	 * @method GetBackLeftAngle
	 * @return フリッパーの角度
	 */
	double GetBackLeftAngle(void);

	/*!
	 * 左前方フリッパーの角度を設定する
	 * @method SetBackLeftAngle
	 * @param  iValue   フリッパーの角度
	 * @return なし
	 */
	void SetBackLeftAngle(const double iValue);

private:
	RTC::TimedDoubleSeq& m_Port;	/*!< ラッピングする変数の参照変数	*/
};

#endif//FLIPPER_ANGLE_WRAPPER_H
