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


// typedef for serial communication
typedef unsigned char uchar;

// typedef boolean
typedef enum
{
  FALSE = 0,
  TRUE = 1,
}t_bool;

// サーボモーターに書き込むデータ
typedef struct
{
  t_bool LED;
  t_bool TorqueON;
  
  int CW_ComplianceMargin;
  int CCW_ComplianceMargin;
  
  int CW_ComplianceSlope;
  int CCW_ComplianceSlope;
  
  double Angle;	//degree
  double Speed;	//rpm
  double Torque;	//%
}t_servoWrite;

// サーボモーターから読み取るデータ
typedef struct
{
  double Angle;	//degree
  double Speed;	//rpm
  double Torque;	//%
}t_servoRead;

// サーボモーターの情報
typedef struct
{
  int id;
  t_servoWrite write;
  t_servoRead read;
}t_servo;

// ロボットアームの情報
typedef struct
{
	t_servo servo[ARM_FREEDOM];
}t_arm;

typedef struct
{
  short Upper;
  short Lower;
}CLimit;

typedef struct
{
  short Upper;
  short Lower;
}JLimit;

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
  int fd;
  t_arm armdata;
  Cartesian CRANECartesianLimit;
  JLimit CRANEJointLimit[5];

  //private関数の定義
  // シリアル通信関数
  uchar calcRobotisCheckSum(uchar *buf, int sizeofArray);
  int GetStatusPacket(uchar *recv);
  void CheckStatusPacket(void);
  void WriteData2Bytes(uchar *buf, t_servoWrite data);
  void RegWrite(int id, t_servoWrite data);
  void Action(void);
  void serialWrite(uchar *buf, int length);
  void initPacket(uchar *buf);
  void getArmStatus(t_arm *arm);
  void GetStatus(t_servo *servo);
public:

  //コンストラクタ
  CRANE();

  // シリアル通信関数
  void openSerialPort(const char *SERIAL_PORT);

  
  // 初期化関数
  void initServo(int id, t_servo *servo);
  void initArm();

  //private変数セット関数
  void setCRANEJointdata(double JointPos[]);
  void setCRANESpeeddata(double spdRatio);
  void setCRANECartesianLimit(Cartesian CartesianLimit);
  void setCRANEJointLimit(JLimit JointLimit[]);

  //private変数ゲット関数
  void getCRANEJointdata(double JointPos[]);
  void getCRANESpeeddata(double spdRatio);
  void getCRANECartesianLimit(Cartesian CartesianLimit);
  void getCRANEJointLimit(JLimit JointLimit[]);
  
  // その他関数
  void ServoOnOff(int torque);
  void kinematics(double x, double y, double z, double JointPos[]);
  void ArmAction();
  void CRANEcloseGripper();
  void CRANEopenGripper();
  void CRANEmoveGripper(double angleRatio);
  int CartesianLimitJudgement( double x , double y , double z );
  int JointLimitJudgement();
  int CRANELimitJudgement(double x, double y, double z);

/********* 関数のプロトタイプ宣言の終了 *********/
 
};

/**************** extern 宣言 *****************/
extern CRANE crane;



#endif//__DEFRETURNID_H__
