/*!
 * @file MotorLoadWrapper.h
 * @brief モータの負荷入出力のラッパークラス
 * @author C.Saito
 * @date 2019/06/19
 */

#ifndef MOTOR_LOAD_WRAPPER_H
#define MOTOR_LOAD_WRAPPER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <cstdint>

/*!
 * @brief モータの負荷入出力のラッパークラス
 * @details 次のdouble型配列で提供するデータの操作APIを提供する
 *          [0]: 右メインモータの負荷
 *          [1]: 左メインモータの負荷
 *          [2]: 右前方サブモータの負荷
 *          [3]: 左前方サブモータの負荷
 *          [4]: 右後方サブモータの負荷
 *          [5]: 左後方サブモータの負荷
 */
class MotorLoadWrapper
{
public:
	/*!
	 * コンストラクタ
	 * @method MotorLoadWrapper
	 * @param  Port   ラッピングする変数
	 */
	MotorLoadWrapper(RTC::TimedDoubleSeq& Port);

	/*!
	 * デストラクタ
	 * @method MotorLoadWrapper
	 */
	virtual ~MotorLoadWrapper();

	/*!
	 * 代入演算子のオーバーロード
	 * @method operator=
	 */
	MotorLoadWrapper& operator=(const MotorLoadWrapper& rhs);

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
	 * 右メインモータの負荷を取得する
	 * @method GetRightMotorLoad
	 * @return モータの負荷
	 */
	double GetRightMotorLoad(void);

	/*!
	 * 右メインモータの負荷を設定する
	 * @method SetRightMotorLoad
	 * @param  dValue   モータの負荷
	 * @return なし
	 */
	void SetRightMotorLoad(const double dValue);

	/*!
	 * 左メインモータの負荷を取得する
	 * @method GetLeftMotorLoad
	 * @return モータの負荷
	 */
	double GetLeftMotorLoad(void);

	/*!
	 * 左メインモータの負荷を設定する
	 * @method SetLeftMotorLoad
	 * @param  dValue   モータの負荷
	 * @return なし
	 */
	void SetLeftMotorLoad(const double dValue);

	/*!
	 * 右前方サブモータの負荷を取得する
	 * @method GetFrontRightMotorLoad
	 * @return モータの負荷
	 */
	double GetFrontRightMotorLoad(void);

	/*!
	 * 右前方サブモータの負荷を設定する
	 * @method SetFrontRightMotorLoad
	 * @param  dValue   モータの負荷
	 * @return なし
	 */
	void SetFrontRightMotorLoad(const double dValue);

	/*!
	 * 左前方サブモータの負荷を取得する
	 * @method GetFrontLeftMotorLoad
	 * @return モータの負荷
	 */
	double GetFrontLeftMotorLoad(void);

	/*!
	 * 左前方サブモータの負荷を設定する
	 * @method SetFrontLeftMotorLoad
	 * @param  dValue   モータの負荷
	 * @return なし
	 */
	void SetFrontLeftMotorLoad(const double dValue);

	/*!
	 * 右後方サブモータの負荷を取得する
	 * @method GetBackRightMotorLoad
	 * @return モータの負荷
	 */
	double GetBackRightMotorLoad(void);

	/*!
	 * 右後方サブモータの負荷を設定する
	 * @method SetBackRightMotorLoad
	 * @param  dValue   モータの負荷
	 * @return なし
	 */
	void SetBackRightMotorLoad(const double dValue);

	/*!
	 * 左後方サブモータの負荷を取得する
	 * @method GetBackLeftMotorLoad
	 * @return モータの負荷
	 */
	double GetBackLeftMotorLoad(void);

	/*!
	 * 左後方サブモータの負荷を設定する
	 * @method SetBackLeftMotorLoad
	 * @param  dValue   モータの負荷
	 * @return なし
	 */
	void SetBackLeftMotorLoad(const double dValue);

private:
	RTC::TimedDoubleSeq& m_Port;	/*!< ラッピングする変数の参照変数	*/
};

#endif//MOTOR_LOAD_WRAPPER_H
