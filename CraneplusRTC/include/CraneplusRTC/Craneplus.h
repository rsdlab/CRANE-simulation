//Craneplus.h
#ifndef __Craneplus_H__
#define __Craneplus_H__

//���w�萔�̎g�p
#define _USE_MATH_DEFINES

/********* include�t�@�C�� *********/
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>

#ifdef _WIN32
#include "SerialCommunication.h"

#else
//linux******************
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
//*******************

#endif


/********* �L���萔 *********/

// �A�[�����R�x (CRANE+ has 5 freedom)
#define ARM_FREEDOM	5

// �A�[���̃����N�̒���
#define r1      83
#define r2      93.5
#define r3      138

//��1�����[�^�̉��͈�
#define	Angle1_LimitMax	300
#define	Angle1_LimitMin	0
//��2�����[�^�̉��͈�
#define	Angle2_LimitMax	300
#define	Angle2_LimitMin 0
//��3�����[�^�̉��͈�
#define	Angle3_LimitMax	300
#define	Angle3_LimitMin	0
//��4�����[�^�̉��͈�
#define	Angle4_LimitMax	300
#define	Angle4_LimitMin	0
//��5�����[�^�̉��͈�

//X�����͈�[mm]
#define X_LimitMax   329
#define X_LimitMin   -300
//Y�����͈�[mm]
#define Y_LimitMax   314.5
#define Y_LimitMin   -314.5
//Z�����͈�[mm]
#define Z_LimitMax   359.9
#define Z_LimitMin   0

//�n���h�̉��͈�
#define Hand_LimitMax	   130
#define Hand_LimitMin	   185


/********* �L���萔�̏I�� *********/



/********* Type define *********/

typedef unsigned char uchar;

//�T�[�{�ɏ������ރf�[�^
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

//CRANE�̃W���C���g���~�b�g�̍\����
typedef struct
{
  short Upper;
  short Lower;
}JLimit;

//CRANE�̉��͈̓��~�b�g�̍\����
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



/******************�N���X��`*********************/ 
class Craneplus{
 private:

  //private�ϐ��̐錾
  char *dev;
  ServoWrite Writedata[ARM_FREEDOM]; //Writedata[0]�̓T�[�{ID1�̃f�[�^
  double ReadAngle[ARM_FREEDOM];
  Cartesian CRANECartesianLimit;
  JLimit CRANEJointLimit[5];
#ifdef WIN32
  SerialCommunication sc;
#else
  int fd;
  struct termios newtio;
#endif
  //private�֐��̒�`
  //�V���A���ʐM�֐�

  //�V���A���ʐM�Ńf�[�^�𑗐M����
  void serialWrite(uchar *buf, int length);

  //�V���A���ʐM�Ńf�[�^����M����
  void serialRead(uchar *buf, int length);

  //�V���A���ʐM�p�̃`�F�b�N�T�����v�Z����
  uchar calcCheckSum(uchar *buf, int Datasize);

  //�V���A���ʐM�ł��Ă��邩�m�F����
  void checkserial();

  //Dynamixel��RegWrite�Ńf�[�^�𑗐M����
  void RegWrite(int id, ServoWrite data[]);

  //Dynamixel��Action�Ńf�[�^�𑗐M����
  void Action(void);

  //�T�[�{��Angle�l���󂯎��
  void ReadServoAngle(int id, double ReadAngle[]);

  //�A�[���̊e�֐߂�Angle�l���󂯎��
  void ReadArmAngle();
public:

  //�R���X�g���N�^
  Craneplus();

  //�V���A���ʐM�֐�
  //�V���A���ʐM���J�n����
  int OpenCOMDevice(const char *SERIAL_PORT);

  //�V���A���ʐM���I������
  void CloseCOMDevice();
  

  // �������֐�
  //�T�[�{���[�^�[�ɑ���f�[�^�̕ϐ�������������֐�

  void initServo(int id, ServoWrite data[]);
  //���ׂẴT�[�{���[�^�[�ɑ���f�[�^�̕ϐ�������������֐�

  void initArm();

  //private�ϐ��Z�b�g�֐�
  //JointPos[]�̒l��Writedata[].Angle�ɏ�������
  void setCRANEJointdata(double JointPos[]);

  //spdRatio�̒l��Writedata[].Speed�ɏ�������
  void setCRANESpeeddata(int id, double spdRatio);

  //CartesianLimit�̒l��CRANECartesianLimit�ɏ�������
  void setCRANECartesianLimit(Cartesian CartesianLimit);

  //JointLimit[]�̒l��CRANEJointLimit[]�ɏ�������
  void setCRANEJointLimit(JLimit JointLimit[]);


  //private�ϐ��Q�b�g�֐�
  //�N���X���̕ϐ��̊p�x�f�[�^����肷��
  void getCRANEJointdata(double JointPos[]);

  //�N���X���̕ϐ��̑��x�f�[�^����肷��
  void getCRANESpeeddata(double spdRatio);

  //�N���X���̕ϐ��͈̔̓��~�b�g�f�[�^����肷��
  void getCRANECartesianLimit(Cartesian CartesianLimit);

  //�N���X���̕ϐ��͈̔̓��~�b�g�f�[�^����肷��
  void getCRANEJointLimit(JLimit JointLimit[]);

  
  // CRANE+�Ɋւ���֐�
  //Dynamixel��Write_Data�ŃT�[�{���[�^�[�̃g���N��OnOff������
  void ServoOnOff(int torque);

  //Dynamixel��RegWrite-Action��Writedata[]�ɏ������܂ꂽ�f�[�^��Dynamixel�ɑ��M����
  void ArmAction();

  //CRANE�̃n���h�����
  void CRANEcloseGripper();

  //CRANE�̃n���h���J��
  void CRANEopenGripper();

  //CRANE�̃n���h�w�肵���J�x�ł��J��
  void CRANEmoveGripper(double angleRatio);

  //Catesian�\�t�g���~�b�g�̔�����s��
  int CartesianLimitJudgement( double x , double y , double z );

  //Joint�\�t�g���~�b�g�̔�����s��
  int JointLimitJudgement();

  //CRANE+���~�b�g�̔�����s��
  int CRANELimitJudgement(double x, double y, double z);

  //�A�[���̋t�^���w���v�Z����
  void kinematics(double x, double y, double z, double JointPos[]);



/********* �֐��̃v���g�^�C�v�錾�̏I�� *********/
 
};

/**************** extern �錾 *****************/
extern Craneplus crane;

#endif//__Craneplus_H__
