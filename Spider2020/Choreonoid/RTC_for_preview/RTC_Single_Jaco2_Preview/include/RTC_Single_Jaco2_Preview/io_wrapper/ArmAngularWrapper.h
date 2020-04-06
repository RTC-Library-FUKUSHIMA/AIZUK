/*!
 * @file ArmAngularWrapper.h
 * @brief Jaco2アームの腕の角度入出力のラッパークラス
 * @author C.Saito
 * @date 2019/12/27
 */

#ifndef ARM_ANGULAR_WRAPPER_H
#define ARM_ANGULAR_WRAPPER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <cstdint>

/*!
 * @brief Jaco2アームの腕の角度入出力のラッパークラス
 * @details 次のdouble型配列で提供するデータの操作APIを提供する
 *          [0]: Shoulderの角度
 *          [1]: Armの角度
 *          [2]: Forearmの角度
 *          [3]: Wrist1の角度
 *          [4]: Wrist2の角度
 *          [5]: Handの角度
 */
class ArmAngularWrapper
{
public:
	/*!
	 * コンストラクタ
	 * @method ArmAngularWrapper
	 * @param  Port   ラッピングする変数
	 */
	ArmAngularWrapper(RTC::TimedDoubleSeq& Port);

	/*!
	 * デストラクタ
	 * @method ArmAngularWrapper
	 */
	virtual ~ArmAngularWrapper();

	/*!
	 * 代入演算子のオーバーロード
	 * @method operator=
	 */
	ArmAngularWrapper& operator=(const ArmAngularWrapper& rhs);

	/*!
	 * タイムスタンプを設定する
	 * @method SetTimestamp
	 * @return なし
	 */
	void SetTimestamp(void);

	/*!
	 * Jaco2アームの腕の角度の入出力の配列数と値を初期化する
	 * @method InitData
	 * @return なし
	 */
	void InitData(void);

	/*!
	 * Jaco2アームの腕の角度の数を取得する
	 * @method GetNumber
	 * @return データの数
	 */
	 uint8_t GetNumber(void);

	/*!
	 * Shoulderの角度を取得する
	 * @method GetShoulderAngular
	 * @return Shoulderの角度
	 */
	double GetShoulderAngular(void);

	/*!
	 * Shoulderの角度を設定する
	 * @method SetShoulder
	 * @param  dValue   Shoulderの角度
	 * @return なし
	 */
	void SetShoulderAngular(const double dValue);

	/*!
	 * Armの角度を取得する
	 * @method GetArmAngular
	 * @return Armの角度
	 */
	double GetArmAngular(void);

	/*!
	 * Armの角度を設定する
	 * @method SetArmAngular
	 * @param  dValue   Armの角度
	 * @return なし
	 */
	void SetArmAngular(const double dValue);

	/*!
	 * Forearmの角度を取得する
	 * @method GetForearm
	 * @return Forearmの角度
	 */
	double GetForearmAngular(void);

	/*!
	 * Forearmの角度を設定する
	 * @method SetForearmAngular
	 * @param  dValue   ForearmAngularの角度
	 * @return なし
	 */
	void SetForearmAngular(const double dValue);

	/*!
	 * Wrist1の角度を取得する
	 * @method GetWrist1
	 * @return Wrist1の角度
	 */
	double GetWrist1Angular(void);

	/*!
	 * Wrist1の角度を設定する
	 * @method SetWrist1Angular
	 * @param  dValue   Wrist1の角度
	 * @return なし
	 */
	void SetWrist1Angular(const double dValue);

	/*!
	 * Wrist2の角度を取得する
	 * @method GetWrist2
	 * @return Wrist2の角度
	 */
	double GetWrist2Angular(void);

	/*!
	 * Wrist2の角度を設定する
	 * @method SetWrist2Angular
	 * @param  dValue   Wrist2の角度
	 * @return なし
	 */
	void SetWrist2Angular(const double dValue);

	/*!
	 * Handの角度を取得する
	 * @method GetHand
	 * @return Handの角度
	 */
	double GetHandAngular(void);

	/*!
	 * Handの角度を設定する
	 * @method SetHandAngular
	 * @param  dValue   Handの角度
	 * @return なし
	 */
	void SetHandAngular(const double dValue);

private:
	RTC::TimedDoubleSeq& m_Port;	/*!< ラッピングする変数の参照変数	*/
};

#endif//ARM_ANGULAR_WRAPPER_H
