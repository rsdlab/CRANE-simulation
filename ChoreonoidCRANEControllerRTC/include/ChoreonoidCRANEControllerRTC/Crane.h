//Crane.h
#ifndef __CRANE_H__
#define __CRANE_H__

//数学定数の使用
#define _USE_MATH_DEFINES

/********* includeファイル *********/
#include <cmath>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>

/********* 記号定数 *********/

// アーム自由度 (CRANE+ has 5 freedom)
#define ARM_FREEDOM	5

// アームのリンクの長さ
#define r1      83
#define r2      93.5
#define r3      138

//第1軸モータの可動範囲
#define	Angle1_LimitMax	300
#define	Angle1_LimitMin	0
//第2軸モータの可動範囲
#define	Angle2_LimitMax	300
#define	Angle2_LimitMin 0
//第3軸モータの可動範囲
#define	Angle3_LimitMax	300
#define	Angle3_LimitMin	0
//第4軸モータの可動範囲
#define	Angle4_LimitMax	300
#define	Angle4_LimitMin	0
//第5軸モータの可動範囲

//X軸可動範囲[mm]
#define X_LimitMax   329
#define X_LimitMin   -300
//Y軸可動範囲[mm]
#define Y_LimitMax   314.5
#define Y_LimitMin   -314.5
//Z軸可動範囲[mm]
#define Z_LimitMax   359.9
#define Z_LimitMin   0

//ハンドの可動範囲
#define Hand_LimitMax	   130
#define Hand_LimitMin	   185


/********* 記号定数の終了 *********/



/********* Type define *********/

typedef unsigned char uchar;

//サーボに書き込むデータ
typedef struct
{
  int CW_ComplianceMargin;
  int CCW_ComplianceMargin;
  
  int CW_ComplianceSlope;
  int CCW_ComplianceSlope;
  
  double Angle;	//degree
  double Speed;	//rpm
  double Torque;//%
}ServoWrite;

//CRANEのジョイントリミットの構造体
typedef struct
{
  short Upper;
  short Lower;
}JLimit;

//CRANEの可動範囲リミットの構造体
typedef struct
{
  short Upper;
  short Lower;
}CLimit;

typedef struct
{
  CLimit x;
  CLimit y;
  CLimit z;
}Cartesian;

/********* END Type define *********/



/******************クラス定義*********************/ 
class CRANE{
 private:

  //private変数の宣言
  char *dev;
  int fd;
  ServoWrite Writedata[ARM_FREEDOM]; //Writedata[0]はサーボID1のデータ
  double ReadAngle[ARM_FREEDOM];
  Cartesian CRANECartesianLimit;
  JLimit CRANEJointLimit[5];
  //Structure for Saving now setting
  struct termios newtio;

  //private関数の定義
  // シリアル通信関数
  void serialWrite(uchar *buf, int length);
  uchar calcCheckSum(uchar *buf, int Datasize);
  void checkserial();
  void RegWrite(int id, ServoWrite data[]);
  void Action(void);
  void ReadServoAngle(int id, double ReadAngle[]);
  void ReadArmAngle();
public:

  //コンストラクタ
  CRANE();

  // シリアル通信関数
  int OpenCOMDevice(const char *SERIAL_PORT);
  void CloseCOMDevice();
  
  // 初期化関数
  void initServo(int id, ServoWrite data[]);
  void initArm();

  //private変数セット関数
  void setCRANEJointdata(double JointPos[]);
  void setCRANESpeeddata(int id, double spdRatio);
  void setCRANECartesianLimit(Cartesian CartesianLimit);
  void setCRANEJointLimit(JLimit JointLimit[]);

  //private変数ゲット関数
  void getCRANEJointdata(double JointPos[]);
  void getCRANESpeeddata(double spdRatio);
  void getCRANECartesianLimit(Cartesian CartesianLimit);
  void getCRANEJointLimit(JLimit JointLimit[]);
  
  // CRANE+に関する関数
  void ServoOnOff(int torque);
  void ArmAction();
  void CRANEcloseGripper();
  void CRANEopenGripper();
  void CRANEmoveGripper(double angleRatio);
  int CartesianLimitJudgement( double x , double y , double z );
  int JointLimitJudgement();
  int CRANELimitJudgement(double x, double y, double z);
  void kinematics(double x, double y, double z, double JointPos[]);


/********* 関数のプロトタイプ宣言の終了 *********/
 
};

/**************** extern 宣言 *****************/
extern CRANE crane;

#endif//__DEFRETURNID_H__
