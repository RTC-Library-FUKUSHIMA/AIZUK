// -*- C++ -*-
/*!
 * @file MainMotorProcessor.h
 * @brief メインモータの情報処理クラス
 * @author C.Saito
 * @date 2019/06/24
 */

#ifndef MAIN_MOTOR_PROCESSOR_H
#define MAIN_MOTOR_PROCESSOR_H

#include "Motor.h"
#include <string>

/*!
 * メインモータの情報処理クラス
 */
class MainMotorProcessor
{
public:
	/*!
	 * コンストラクタ
	 * @method MainMotorProcessor
	 */
	MainMotorProcessor();

	/*!
	 * デストラクタ
	 * @method ~MainMotorProcessor
	 */
	virtual ~MainMotorProcessor();

	/*!
	 * メインモータのデータを初期化する
	 * @method InitData
	 * @return なし
	 */
	void InitData(void);

	/*!
	 * メインモータのフィードバックデータを初期化する
	 * @method InitFeedbackData
	 * @return なし
	 */
	void InitFeedbackData(void);

	/*!
	 * メインモータの動作コマンドを生成する
	 * @method GenMoveCommand
	 * @param  [in] dVx            目標の２次元の並進速度(X)
	 * @param  [in] dVy            目標の２次元の並進速度(Y)
	 * @param  [in] dVa            目標の２次元の回転速度
	 * @return 動作コマンド
	 */
	std::string GenMoveCommand(double dVx, double dVy, double dVa);

	/*!
	 * メインモータの停止の動作コマンドを生成する
	 * @method GenStopCommand
	 * @return 動作コマンド
	 */
	std::string GenStopCommand(void);

	/*!
	 * フィードバックを解析する
	 * @method AnalyzeFeedback
	 * @param  [in] dFrequency     周期
	 * @param  [in] dVx            目標の２次元の並進速度(X)
	 * @param  [in] dVy            目標の２次元の並進速度(Y)
	 * @param  [in] dVa            目標の２次元の回転速度
	 * @param  [in] sFeedback       フィードバック文字列
	 */
	bool AnalyzeFeedback(double dFrequency, double dVx, double dVy, double dVa, std::string sFeedback);

	/*!
	 * モータの回転から２次元の位置姿勢を求める
	 * @method CalcOdometry
	 * @param  [in] dFrequency   周期
	 */
	void CalcOdometry(double dFrequency);

	/*!
	 * モータの回転及びIMUの姿勢から３次元の位置姿勢を求める
	 * @method CalcOdometry
	 * @param  [in] dRoll        外部観測したロール角
	 * @param  [in] dPitch       外部観測したピッチ角
	 * @param  [in] dYaw         外部観測したヨー角
	 * @param  [in] dFrequency   周期
	 */
	void CalcOdometry(double dRoll, double dPitch, double dYaw, double dFrequency);

	/*!
	 * オドメトリ及び速度制御に使用するコンフィグレーションを設定する
	 * @method SetConfig
	 * @param  [in] dTurningRadius 旋回半径
	 * @param  [in] dKP            PID制御の比例ゲイン
	 * @param  [in] dKI            PID制御の積分ゲイン
	 * @param  [in] dKD            PID制御の微分ゲイン
	 * @param  [in] dVxGain        オドメトリの並進距離を実測に近づけるための係数
	 * @param  [in] dVaGain        オドメトリの旋回を実測に近づけるための係数
	 */
	void SetConfig(double dTurningRadius, double dKP, double dKI, double dKD, double dVxGain, double dVaGain);

	/*!
	 * 右メインモータのコンフィグレーションを設定する
	 * @method SetConfigR
	 * @param  [in] iDirection   モータの回転方向
	 * @param  [in] iPulseNumber モータのパルス数
	 * @param  [in] dRadius      車輪の半径
	 * @param  [in] dGearRatio   モータと車輪の減速比
	 * @param  [in] dLoadGain    電圧値をモータ負荷に変換するゲイン
	 * @param  [in] dLoadBase    モータ負荷の基準電圧
	 */
	void SetConfigR(int8_t iDirection, int32_t iPulseNumber, double dRadius, double dGearRatio, double dLoadGain, double dLoadBase);

	/*!
	 * 左メインモータのコンフィグレーションを設定する
	 * @method SetConfigL
	 * @param  [in] iDirection   モータの回転方向
	 * @param  [in] iPulseNumber モータのパルス数
	 * @param  [in] dRadius      車輪の半径
	 * @param  [in] dGearRatio   モータと車輪の減速比
	 * @param  [in] dLoadGain    電圧値をモータ負荷に変換するゲイン
	 * @param  [in] dLoadBase    モータ負荷の基準電圧
	 */
	void SetConfigL(int8_t iDirection, int32_t iPulseNumber, double dRadius, double dGearRatio, double dLoadGain, double dLoadBase);

	/*!
	 * 右モータの負荷を取得する
	 * @method GetLoadR
	 * @return 負荷
	 */
	double GetLoadR(void);

	/*!
	 * 左モータの負荷を取得する
	 * @method GetLoadL
	 * @return 負荷
	 */
	double GetLoadL(void);

	/*!
	 * 旋回半径を取得する
	 * @method GetTurningRadius
	 * @return 旋回半径
	 */
	double GetTurningRadius(void);

	/*!
	 * 旋回半径を設定する
	 * @method SetTurningRadius
	 * @param  [in] dValue 旋回半径
	 * @return なし
	 */
	void SetTurningRadius(double dValue);

	/*!
	 * PID速度制御の比例ゲインを取得する
	 * @method GetKP
	 * @return ゲイン
	 */
	double GetKP(void);

	/*!
	 * PID速度制御の比例ゲインを設定する
	 * @method SetKP
	 * @param  [in] dValue ゲイン
	 * @return なし
	 */
	void SetKP(double dValue);

	/*!
	 * PID速度制御の積分ゲインを取得する
	 * @method GetKI
	 * @return ゲイン
	 */
	double GetKI(void);

	/*!
	 * PID速度制御の積分ゲインを設定する
	 * @method SetKI
	 * @param  [in] dValue ゲイン
	 * @return なし
	 */
	void SetKI(double dValue);

	/*!
	 * PID速度制御の微分ゲインを取得する
	 * @method GetKD
	 * @return ゲイン
	 */
	double GetKD(void);

	/*!
	 * PID速度制御の微分ゲインを設定する
	 * @method SetKD
	 * @param  [in] dValue ゲイン
	 * @return なし
	 */
	void SetKD(double dValue);

	/*!
	 * オドメトリの並進速度(X)のゲインを取得する
	 * @method GetVxGain
	 * @return ゲイン
	 */
	double GetVxGain(void);

	/*!
	 * オドメトリの並進速度(X)のゲインを設定する
	 * @method SetVxGain
	 * @param  [in] dValue ゲイン
	 * @return なし
	 */
	void SetVxGain(double dValue);

	/*!
	 * オドメトリの回転速度のゲインを取得する
	 * @method GetVaGain
	 * @return ゲイン
	 */
	double GetVaGain(void);

	/*!
	 * オドメトリの回転速度のゲインを設定する
	 * @method SetVaGain
	 * @param  [in] dValue ゲイン
	 * @return なし
	 */
	void SetVaGain(double dValue);

	/*!
	 * ２次元の並進速度(X)を取得する
	 * @method GetVx
	 * @return 速度
	 */
	double GetVx(void);

	/*!
	 * ２次元の並進速度(X)を設定する
	 * @method SetVx
	 * @param  [in] dValue 速度
	 * @return なし
	 */
	void SetVx(double dValue);

	/*!
	 * ２次元の並進速度(Y)を取得する
	 * @method GetVy
	 * @return 速度
	 */
	double GetVy(void);

	/*!
	 * ２次元の並進速度(Y)を設定する
	 * @method SetVy
	 * @param  [in] dValue 速度
	 * @return なし
	 */
	void SetVy(double dValue);

	/*!
	 * ２次元の回転速度を取得する
	 * @method GetVa
	 * @return 角速度
	 */
	double GetVa(void);

	/*!
	 * ２次元の回転速度を設定する
	 * @method SetVa
	 * @param  [in] dValue 角速度
	 * @return なし
	 */
	void SetVa(double dValue);

	/*!
	 * ３次元の位置(X)を取得する
	 * @method GetPositionX
	 * @return 座標
	 */
	double GetPositionX(void);

	/*!
	 * ３次元の位置(X)を設定する
	 * @method SetPositionX
	 * @param  [in] dValue 座標
	 * @return なし
	 */
	void SetPositionX(double dValue);

	/*!
	 * ３次元の位置(Y)を取得する
	 * @method GetPositionY
	 * @return 座標
	 */
	double GetPositionY(void);

	/*!
	 * ３次元の位置(Y)を設定する
	 * @method SetPositionY
	 * @param  [in] dValue 座標
	 * @return なし
	 */
	void SetPositionY(double dValue);

	/*!
	 * ３次元の位置(Z)を取得する
	 * @method GetPositionZ
	 * @return 座標
	 */
	double GetPositionZ(void);

	/*!
	 * ３次元の位置(Z)を設定する
	 * @method SetPositionZ
	 * @param  [in] dValue 座標
	 * @return なし
	 */
	void SetPositionZ(double dValue);

	/*!
	 * ３次元の姿勢(Roll)を取得する
	 * @method GetOrientationR
	 * @return 姿勢
	 */
	double GetOrientationR(void);

	/*!
	 * ３次元の姿勢(Roll)を設定する
	 * @method SetOrientationR
	 * @param  [in] dValue 姿勢
	 * @return なし
	 */
	void SetOrientationR(double dValue);

	/*!
	 * ３次元の姿勢(Pitch)を取得する
	 * @method GetOrientationP
	 * @return 姿勢
	 */
	double GetOrientationP(void);

	/*!
	 * ３次元の姿勢(Pitch)を設定する
	 * @method SetOrientationP
	 * @param  [in] dValue 姿勢
	 * @return なし
	 */
	void SetOrientationP(double dValue);

	/*!
	 * ３次元の姿勢(Yaw)を取得する
	 * @method GetOrientationY
	 * @return 姿勢
	 */
	double GetOrientationY(void);

	/*!
	 * ３次元の姿勢(Yaw)を設定する
	 * @method SetOrientationY
	 * @param  [in] dValue 姿勢
	 * @return なし
	 */
	void SetOrientationY(double dValue);

	/*!
	 * 右モータのPID速度制御の積分項を取得する
	 * @method GetIntegralR
	 * @return 積分項
	 */
	double GetIntegralR(void);

	/*!
	 * 右モータのPID速度制御の積分項を設定する
	 * @method SetIntegralR
	 * @param  [in] dValue 積分項
	 * @return なし
	 */
	void SetIntegralR(double dValue);

	/*!
	 * 左モータのPID速度制御の積分項を取得する
	 * @method GetIntegralL
	 * @return 積分項
	 */
	double GetIntegralL(void);

	/*!
	 * 左モータのPID速度制御の積分項を設定する
	 * @method SetIntegralL
	 * @param  [in] dValue 積分項
	 * @return なし
	 */
	void SetIntegralL(double dValue);

private:
	double m_dTurningRadius;	/*!< 旋回半径							*/
	double m_dKP;				/*!< PID速度制御の比例ゲイン			*/
	double m_dKI;				/*!< PID速度制御の積分ゲイン			*/
	double m_dKD;				/*!< PID速度制御の微分ゲイン			*/
	double m_dVxGain;			/*!< オドメトリの並進速度(X)のゲイン	*/
	double m_dVaGain;			/*!< オドメトリの回転速度のゲイン		*/

	double m_dVx;				/*!< ２次元の並進速度(X)				*/
	double m_dVy;				/*!< ２次元の並進速度(Y)				*/
	double m_dVa;				/*!< ２次元の回転速度					*/
	double m_dPositionX;		/*!< ３次元の位置(X)					*/
	double m_dPositionY;		/*!< ３次元の位置(Y)					*/
	double m_dPositionZ;		/*!< ３次元の位置(Z)					*/
	double m_dOrientationR;		/*!< ３次元の姿勢(Roll)					*/
	double m_dOrientationP;		/*!< ３次元の姿勢(Pitch)				*/
	double m_dOrientationY;		/*!< ３次元の姿勢(Yaw)					*/
	double m_dIntegralR;		/*!< 右モータのPID速度制御の積分項		*/
	double m_dIntegralL;		/*!< 左モータのPID速度制御の積分項		*/

	Motor m_MotorR;				/*!< 右モータ							*/
	Motor m_MotorL;				/*!< 左モータ							*/
};

#endif//MAIN_MOTOR_PROCESSOR_H
