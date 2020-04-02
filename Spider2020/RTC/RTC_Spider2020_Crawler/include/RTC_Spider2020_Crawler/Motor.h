// -*- C++ -*-
/*!
 * @file Motor.h
 * @brief モータの情報処理クラス
 * @author C.Saito
 * @date 2019/06/25
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <cstdint>

/*!
 * モータの情報管理クラス
 */
class Motor
{
public:
	/*!
	 * コンストラクタ
	 * @method Motor
	 */
	Motor();

	/*!
	 * デストラクタ
	 * @method ~Motor
	 */
	virtual ~Motor();

	/*!
	 * モータのデータを初期化する
	 * @method InitData
	 * @return なし
	 */
	void InitData(void);

	/*!
	 * モータのフィードバックデータを初期化する
	 * @method InitFeedbackData
	 * @return なし
	 */
	void InitFeedbackData(void);

	/*!
	 * モータのフィードバックを処理する
	 * @method CalcFeedback
	 * @param  [in] dFrequency   周期
	 * @param  [in] iPulseCount  パルスカウント
	 * @param  [in] dVelocityMD  モータの回転速度の電圧値
	 * @param  [in] dLoad        モータの負荷の電圧値
	 */
	void CalcFeedback(double dFrequency, int32_t iPulseCount, double dVelocityMD, double dLoad);

	/*!
	 * モータの回転方向を取得する
	 * @method GetDirection
	 * @return 回転方向(1:時計回り、-1:反時計周り)
	 */
	int8_t GetDirection(void);

	/*!
	 * モータの回転方向を設定する
	 * @method SetDirection
	 * @param  [in] iValue   回転方向(1:時計回り、-1:反時計周り)
	 * @return なし
	 */
	void SetDirection(int8_t iValue);

	/*!
	 * モータのパルス数を取得する
	 * @method GetPulseNumber
	 * @return パルス数
	 */
	int32_t GetPulseNumber(void);

	/*!
	 * モータのパルス数を設定する
	 * @method SetPulseNumber
	 * @param  [in] iValue   パルス数
	 * @return なし
	 */
	void SetPulseNumber(int32_t iValue);

	/*!
	 * 車輪の半径を取得する
	 * @method GetRadius
	 * @return パルス数
	 */
	double GetRadius(void);

	/*!
	 * 車輪の半径を設定する
	 * @method SetRadius
	 * @param  [in] dValue   半径
	 * @return なし
	 */
	void SetRadius(const double dValue);

	/*!
	 * モータと車輪の減速比を取得する
	 * @method GetGearRatio
	 * @return 減速比
	 */
	double GetGearRatio(void);

	/*!
	 * モータと車輪の減速比を設定する
	 * @method SetGearRatio
	 * @param  [in] dValue 減速比
	 * @return なし
	 */
	void SetGearRatio(double dValue);

	/*!
	 * 電圧値をモータ負荷に変換するゲインを取得する
	 * @method GetLoadGain
	 * @return ゲイン
	 */
	double GetLoadGain(void);

	/*!
	 * 電圧値をモータ負荷に変換するゲインを設定する
	 * @method SetLoadGain
	 * @param  [in] dValue ゲイン
	 * @return なし
	 */
	void SetLoadGain(double dValue);

	/*!
	 * モータ負荷の基準電圧を取得する
	 * @method GetLoadBase
	 * @return ゲイン
	 */
	double GetLoadBase(void);

	/*!
	 * モータ負荷の基準電圧を設定する
	 * @method SetLoadBase
	 * @param  [in] dValue 電圧
	 * @return なし
	 */
	void SetLoadBase(double dValue);

	/*!
	 * モータのパルスカウントを取得する
	 * @method GetPulseCount
	 * @return パルスカウント
	 */
	int32_t GetPulseCount(void);

	/*!
	 * モータのパルスカウントを設定する
	 * @method SetPulseCount
	 * @param  [in] iValue   パルスカウント
	 * @return なし
	 */
	void SetPulseCount(int32_t iValue);

	/*!
	 * モータの負荷を取得する
	 * @method GetLoad
	 * @return 負荷
	 */
	double GetLoad(void);

	/*!
	 * モータの負荷を設定する
	 * @method SetLoad
	 * @param  [in] dValue 負荷
	 * @return なし
	 */
	void SetLoad(double dValue);

	/*!
	 * 車輪の角度を取得する
	 * @method GetAngle
	 * @return 角度
	 */
	double GetAngle(void);

	/*!
	 * 車輪の角度を設定する
	 * @method SetAngle
	 * @param  [in] dValue 角度
	 * @return なし
	 */
	void SetAngle(double dValue);

	/*!
	 * 車輪の角速度を取得する
	 * @method GetAngularVelocity
	 * @return 角速度
	 */
	double GetAngularVelocity(void);

	/*!
	 * 車輪の角速度を設定する
	 * @method SetAngularVelocity
	 * @param  [in] dValue 角速度
	 * @return なし
	 */
	void SetAngularVelocity(double dValue);

	/*!
	 * 車輪の角加速度を取得する
	 * @method GetAngularAcceleration
	 * @return 角加速度
	 */
	double GetAngularAcceleration(void);

	/*!
	 * 車輪の角加速度を設定する
	 * @method SetAngularAcceleration
	 * @param  [in] dValue 角加速度
	 * @return なし
	 */
	void SetAngularAcceleration(double dValue);

	/*!
	 * 車輪の速度を取得する
	 * @method GetVelocity
	 * @return 速度
	 */
	double GetVelocity(void);

	/*!
	 * 車輪の速度を設定する
	 * @method SetVelocity
	 * @param  [in] dValue 速度
	 * @return なし
	 */
	void SetVelocity(double dValue);

	/*!
	 * 車輪の加速度を取得する
	 * @method GetAcceleration
	 * @return 加速度
	 */
	double GetAcceleration(void);

	/*!
	 * 車輪の加速度を設定する
	 * @method SetAcceleration
	 * @param  [in] dValue 加速度
	 * @return なし
	 */
	void SetAcceleration(double dValue);

private:
	int8_t m_iDirection;				/*!< モータの回転方向					*/
	int32_t	m_iPulseNumber;				/*!< モータのパルス数					*/
	double m_dRadius;					/*!< 車輪の半径							*/
	double m_dGearRatio;				/*!< モータと車輪の減速比				*/
	double m_dLoadGain;					/*!< 電圧値をモータ負荷に変換するゲイン */
	double m_dLoadBase;					/*!< モータ負荷の基準電圧				*/

	int32_t m_iPulseCount;				/*!< モータのパルスカウント				*/
	double m_dLoad;						/*!< モータの負荷						*/
	double m_dAngle;					/*!< 車輪の角度							*/
	double m_dAngularVelocity;			/*!< 車輪の角速度						*/
	double m_dAngularAcceleration;		/*!< 車輪の角加速度						*/
	double m_dVelocity;					/*!< 車輪の速度							*/
	double m_dAcceleration;				/*!< 車輪の加速度						*/
};

#endif//MOTOR_H
