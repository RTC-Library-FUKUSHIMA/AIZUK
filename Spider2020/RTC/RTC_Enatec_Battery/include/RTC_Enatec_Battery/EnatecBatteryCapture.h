// -*- C++ -*-
/*!
 * @file EnatecBatteryCapture.h
 * @brief エナテック製バッテリの情報の取得クラス
 * @author C.Saito
 * @date 2019/05/30
 */

#ifndef ENATEC_BATTERY_CAPTURE_H
#define ENATEC_BATTERY_CAPTURE_H

#include <stdint.h>
#include <string>

typedef uint8_t BYTE;

/*!
 * エナテック製バッテリの情報の取得クラス
 */
class EnatecBatteryCapture
{
public:
	/*!
	 * コンストラクタ
	 * @method EnatecBatteryCapture
	 */
	EnatecBatteryCapture();

	/*!
	 * デストラクタ
	 * @method ~EnatecBatteryCapture
	 */
	virtual ~EnatecBatteryCapture();

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
	 * 製造会社名を取得する
	 * @method GetMaker
	 * @return 製造会社名
	 */
	std::string GetMaker(void);

	/*!
	 * バッテリ残存容量比を取得する
	 * @method GetCapacityRatio
	 * @retval 0〜100 取得成功
	 * @retval 255 取得失敗
	 */
	BYTE GetCapacityRatio(void);

private:
	/*!
	 * シリアルデータの送受信をする
	 * @method SendAndRecv
	 * @param btCmd
	 * @param pbtStatusBuff
	 * @param btStatusBuffSize
	 * @retval true 成功
	 * @retval false 失敗
	 */
	bool SendAndRecv(BYTE btCmd, BYTE *pbtStatusBuff, BYTE btStatusBuffSize);

	int m_fd;		/*!< ファイルディスクリプタ			*/
};

#endif//ENATEC_BATTERY_CAPTURE_H
