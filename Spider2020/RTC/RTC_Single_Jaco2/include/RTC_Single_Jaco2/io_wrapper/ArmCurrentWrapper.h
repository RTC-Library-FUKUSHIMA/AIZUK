/*!
 * @file ArmCurrentWrapper.h
 * @brief Jaco2アームのモータ負荷の入出力のラッパークラス
 * @author C.Saito
 * @date 2019/12/27
 */

#ifndef ARM_CURRENT_WRAPPER_H
#define ARM_CURRENT_WRAPPER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <cstdint>

/*!
 * @brief モータの負荷入出力のラッパークラス
 * @details 次のdouble型配列で提供するデータの操作APIを提供する
 *          [0]: Shoulderのモータ負荷
 *          [1]: Armのモータ負荷
 *          [2]: Forearmのモータ負荷
 *          [3]: Wrist1のモータ負荷
 *          [4]: Wrist2のモータ負荷
 *          [5]: Handのモータ負荷
 *          [6]: Thumbのモータ負荷
 *          [7]: Index Fingerのモータ負荷
 *          [8]: Middle Fingerのモータ負荷
 */
class ArmCurrentWrapper
{
public:
	/*!
	 * コンストラクタ
	 * @method ArmCurrentWrapper
	 * @param  Port   ラッピングする変数
	 */
	ArmCurrentWrapper(RTC::TimedDoubleSeq& Port);

	/*!
	 * デストラクタ
	 * @method ArmCurrentWrapper
	 */
	virtual ~ArmCurrentWrapper();

	/*!
	 * 代入演算子のオーバーロード
	 * @method operator=
	 */
	ArmCurrentWrapper& operator=(const ArmCurrentWrapper& rhs);

	/*!
	 * タイムスタンプを設定する
	 * @method SetTimestamp
	 * @return なし
	 */
	void SetTimestamp(void);

	/*!
	 * モータの負荷の入出力の配列数と値を初期化する
	 * @method InitData
	 * @return なし
	 */
	void InitData(void);

	/*!
	 * モータの負荷の数を取得する
	 * @method GetNumber
	 * @return データの数
	 */
	 uint8_t GetNumber(void);

	/*!
	 * Shoulderのモータ負荷を取得する
	 * @method GetShoulderCurrent
	 * @return モータ負荷
	 */
	double GetShoulderCurrent(void);

	/*!
	 * Shoulderのモータ負荷を設定する
	 * @method SetShoulderCurrent
	 * @param  dValue   モータ負荷
	 * @return なし
	 */
	void SetShoulderCurrent(const double dValue);

	/*!
	 * Armのモータ負荷を取得する
	 * @method GetArmCurrent
	 * @return モータ負荷
	 */
	double GetArmCurrent(void);

	/*!
	 * Armのモータ負荷を設定する
	 * @method SetArmCurrent
	 * @param  dValue   モータ負荷
	 * @return なし
	 */
	void SetArmCurrent(const double dValue);

	/*!
	 * Forearmのモータ負荷を取得する
	 * @method GetForearmCurrent
	 * @return モータ負荷
	 */
	double GetForearmCurrent(void);

	/*!
	 * Forearmのモータ負荷を設定する
	 * @method SetForearmCurrent
	 * @param  dValue   モータ負荷
	 * @return なし
	 */
	void SetForearmCurrent(const double dValue);

	/*!
	 * Wrist1のモータ負荷を取得する
	 * @method GetWrist1Current
	 * @return モータ負荷
	 */
	double GetWrist1Current(void);

	/*!
	 * Wrist1のモータ負荷を設定する
	 * @method SetWrist1Current
	 * @param  dValue   モータ負荷
	 * @return なし
	 */
	void SetWrist1Current(const double dValue);

	/*!
	 * Wrist2のモータ負荷を取得する
	 * @method GetWrist2Current
	 * @return モータ負荷
	 */
	double GetWrist2Current(void);

	/*!
	 * Wrist2のモータ負荷を設定する
	 * @method SetWrist2Current
	 * @param  dValue   モータ負荷
	 * @return なし
	 */
	void SetWrist2Current(const double dValue);

	/*!
	 * Handのモータ負荷を取得する
	 * @method GetHandCurrent
	 * @return モータ負荷
	 */
	double GetHandCurrent(void);

	/*!
	 * Handのモータ負荷を設定する
	 * @method SetHandCurrent
	 * @param  dValue   モータ負荷
	 * @return なし
	 */
	void SetHandCurrent(const double dValue);

	/*!
	 * Thumbのモータ負荷を取得する
	 * @method GetThumbCurrent
	 * @return モータ負荷
	 */
	double GetThumbCurrent(void);

	/*!
	 * Thumbのモータ負荷を設定する
	 * @method SetThumbCurrent
	 * @param  dValue   モータ負荷
	 * @return なし
	 */
	void SetThumbCurrent(const double dValue);

	/*!
	 * IndexFingerのモータ負荷を取得する
	 * @method GetIndexFingerCurrent
	 * @return モータ負荷
	 */
	double GetIndexFingerCurrent(void);

	/*!
	 * IndexFingerのモータ負荷を設定する
	 * @method SetIndexFingerCurrent
	 * @param  dValue   モータ負荷
	 * @return なし
	 */
	void SetIndexFingerCurrent(const double dValue);

	/*!
	 * MiddleFingerのモータ負荷を取得する
	 * @method GetMiddleFingerCurrent
	 * @return モータ負荷
	 */
	double GetMiddleFingerCurrent(void);

	/*!
	 * MiddleFingerのモータ負荷を設定する
	 * @method SetMiddleFingerCurrent
	 * @param  dValue   モータ負荷
	 * @return なし
	 */
	void SetMiddleFingerCurrent(const double dValue);

private:
	RTC::TimedDoubleSeq& m_Port;	/*!< ラッピングする変数の参照変数	*/
};

#endif//ARM_CURRENT_WRAPPER_H
