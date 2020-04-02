// -*- C++ -*-
/*!
 * @file SubMotorProcessor.h
 * @brief サブモータの情報処理クラス
 * @author C.Saito
 * @date 2019/06/24
 */

#ifndef SUB_MOTOR_PROCESSOR_H
#define SUB_MOTOR_PROCESSOR_H

#include "Motor.h"
#include <string>

/*!
 * サブモータの情報処理クラス
 */
class SubMotorProcessor
{
public:
	/*!
	 * コンストラクタ
	 * @method SubMotorProcessor
	 */
	SubMotorProcessor();

	/*!
	 * デストラクタ
	 * @method ~SubMotorProcessor
	 */
	virtual ~SubMotorProcessor();

	/*!
	 * サブモータのデータを初期化する
	 * @method InitData
	 * @return なし
	 */
	void InitData(void);

	/*!
	 * サブモータのフィードバックデータを初期化する
	 * @method InitFeedbackData
	 * @return なし
	 */
	void InitFeedbackData(void);

	/*!
	 * サブモータの動作コマンドを生成する
	 * @method GetMoveCommand
	 * @param  [in] iPwmR 右モータのPWM指令値
	 * @param  [in] iPwmL 左モータのPWM指令値
	 * @return 動作コマンド
	 */
	std::string GenMoveCommand(int32_t iPwmR, int32_t iPwmL);

	/*!
	 * サブモータの停止の動作コマンドを生成する
	 * @method GenStopCommand
	 * @return 動作コマンド
	 */
	std::string GenStopCommand(void);

	/*!
	 * フィードバックを解析する
	 * @method AnalyzeFeedback
	 * @param  [in] dFrequency      周期
	 * @param  [in] sFeedback       フィードバック文字列
	 * @retval true フィードバック解析成功
	 * @retval false  フィードバック解析失敗
	 */
	bool AnalyzeFeedback(double dFrequency, std::string sFeedback);

	/*!
	 * 右サブモータのコンフィグレーションを設定する
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
	 * 左サブモータのコンフィグレーションを設定する
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
	 * 右モータの角度を取得する
	 * @method GetAngleR
	 * @return 角度
	 */
	double GetAngleR(void);

	/*!
	 * 右モータの角度を設定する
	 * @method SetAngleR
	 * @param [in] dValue 角度
	 * @return なし
	 */
	void SetAngleR(double dValue);

	/*!
	 * 左モータの角度を取得する
	 * @method GetAngleL
	 * @return 角度
	 */
	double GetAngleL(void);

	/*!
	 * 左モータの角度を設定する
	 * @method SetAngleL
	 * @param [in] dValue 角度
	 * @return なし
	 */
	void SetAngleL(double dValue);

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

private:
	Motor m_MotorR;		/*!< 右モータ	*/
	Motor m_MotorL;		/*!< 左モータ	*/

};

#endif//SUB_MOTOR_PROCESSOR_H
