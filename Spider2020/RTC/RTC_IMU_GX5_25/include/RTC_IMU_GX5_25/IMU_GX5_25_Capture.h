// -*- C++ -*-
/*!
 * @file IMU_GX5_25_Capture.h
 * @brief LORD製3DM-GX5-25の情報の取得クラス
 * @author C.Saito
 * @date 2020/02/12
 */

#ifndef IMU_GX5_25_Capture_H
#define IMU_GX5_25_Capture_H

#include "mscl/mscl.h"

/*!
 * LORD製3DM-GX5-25の情報の取得クラス
 */
class IMU_GX5_25_Capture
{
public:
	/*!
	 * コンストラクタ
	 * @method IMU_GX5_25_Capture
	 */
	IMU_GX5_25_Capture();

	/*!
	 * デストラクタ
	 * @method ~IMU_GX5_25_Capture
	 */
	virtual ~IMU_GX5_25_Capture();

	/*!
	 * シリアルポートをオープンする
	 * @method Open
	 * @param  sDeviceName デバイス名
	 * @retval true 成功
	 * @retval false 失敗
	 */
	bool Open(const std::string &sDeviceName);

	/*!
	 * シリアルポートをクローズする
	 * @method Close
	 * @return なし
	 */
	void Close(void);

	/*!
	 * ESTFILTERをリセットする
	 * @method ResetEstFilter
	 * @retval true 成功
	 * @retval false 失敗
	 */
	bool ResetEstFilter(void);

	/*!
	 * ESTFILTERを初期化する
	 * @method InitEstFilter
	 * @param  fRoll         姿勢初期値(ロール)
	 * @param  fPitch        姿勢初期値(ピッチ)
	 * @param  fYaw          姿勢初期値(ヨー)
	 * @retval true 成功
	 * @retval false 失敗
	 */
	bool InitEstFilter(float fRoll, float fPitch, float fYaw);

	/*!
	 * ESTFILTERの加速度をポーリングする
	 * @method PollEstLinearAccel
	 * @return なし
	 */
	bool PollEstLinearAccel(void);

	/*!
	 * ESTFILTERのX軸方向の加速度を取得する
	 * @method GetEstLinearAccelX
	 * @retval X軸方向の加速度
	 */
	float GetEstLinearAccelX(void);

	/*!
	 * ESTFILTERのY軸方向の加速度を取得する
	 * @method GetEstLinearAccelY
	 * @retval Y軸方向の加速度
	 */
	float GetEstLinearAccelY(void);

	/*!
	 * ESTFILTERのZ軸方向の加速度を取得する
	 * @method GetEstLinearAccelZ
	 * @retval Z軸方向の加速度
	 */
	float GetEstLinearAccelZ(void);

	/*!
	 * ESTFILTERクラスのオイラー角をポーリングする
	 * @method PollAhrsEulerAngles
	 * @return なし
	 */
	bool PollEstEulerAngles(void);

	/*!
	 * ESTFILTERクラスのオイラー角のロールを取得する
	 * @method GetEstEulerAnglesR
	 * @retval ロール
	 */
	float GetEstEulerAnglesR(void);

	/*!
	 * ESTFILTERクラスのオイラー角のピッチを取得する
	 * @method GetEstEulerAnglesP
	 * @retval ピッチ
	 */
	float GetEstEulerAnglesP(void);

	/*!
	 * ESTFILTERクラスのオイラー角のヨーを取得する
	 * @method GetEstEulerAnglesY
	 * @retval ヨー
	 */
	float GetEstEulerAnglesY(void);

private:

	mscl::Connection* m_pConnection;	/*!< シリアル接続管理						*/
	float m_fEstLinearAccelX;			/*!< ESTFILTERクラスのX軸方向の加速度		*/
	float m_fEstLinearAccelY;			/*!< ESTFILTERクラスのY軸方向の加速度		*/
	float m_fEstLinearAccelZ;			/*!< ESTFILTERクラスのZ軸方向の加速度		*/
	float m_fEstEulerAnglesR;			/*!< ESTFILTERクラスのオイラー角のロール	*/
	float m_fEstEulerAnglesP;			/*!< ESTFILTERクラスのオイラー角のピッチ	*/
	float m_fEstEulerAnglesY;			/*!< ESTFILTERクラスのオイラー角のヨー		*/

};

#endif//IMU_GX5_25_Capture_H
