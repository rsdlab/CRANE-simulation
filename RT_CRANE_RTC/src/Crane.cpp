#include "Crane.h"

//コンストラクタ
CRANE::CRANE()
{
  t_arm armdata = {0};
}
//クラス宣言
CRANE crane;

/********************************************************************************/
/*                                  private関数                                 */
/********************************************************************************/


/************************************************

	void serialWrite(uchar *buf, int length)

	概要：シリアル通信でデータを送信する

	引数：
              *buf・・・送るデータの配列
              length・・・データの長さ
	
	戻り値：なし

*************************************************/
void CRANE::serialWrite(uchar *buf, int length)
{
	write(fd, buf, length);
	tcflush(fd, TCOFLUSH);
}


/************************************************

	uchar calcRobotisCheckSum(uchar *buf, int sizeofArray)

	概要：チェックサムを計算する

	引数：
              *buf・・・送るデータの配列
              sizeofArray・・・データの数
	
	戻り値：計算結果

*************************************************/
uchar CRANE::calcRobotisCheckSum(uchar *buf, int sizeofArray)
{
	int sum = 0, i;

	buf += 2;	//skip 0xff 0xff

	for(i = 2; i < (sizeofArray - 1); i++)
	{
		sum += *buf;
		buf++;
	}

	return 0xff & (~sum);
}




/************************************************

        int GetStatusPacket(uchar *recv)

	概要：ステータスパケットを受け取る

	引数：
              *recv・・・データを格納する配列
	
	戻り値：ステータスパケット

*************************************************/
int CRANE::GetStatusPacket(uchar *recv)
{
	
	
	read(fd, recv, 4);
	if((recv[0] & recv[1] & 0xff) != 0xff)
	{

		printf("invalid return value:\n%02X %02X %02X %02X \n", recv[0], recv[1], recv[2], recv[3]);
		exit(-1);
	}

	read(fd, recv + 4, recv[3]);

	tcflush(fd, TCIFLUSH);

	return 4 + recv[3];
}


/************************************************

        void CheckStatusPacket(void)

	概要：ステータスパケットを確認する

	引数：なし
              
	戻り値：なし

*************************************************/
void CRANE::CheckStatusPacket(void)
{
	uchar buf[256];
	
	GetStatusPacket(buf);
}



/************************************************

        void WriteData2Bytes(uchar *buf, t_servoWrite data)

	概要：dynamixelに送るデータを格納する

	引数：
              *buf・・・送るデータの配列
              data・・・データに代入する値
	
	戻り値：なし

*************************************************/
void CRANE::WriteData2Bytes(uchar *buf, t_servoWrite data)
{
	int angle = (int)( 1024.0 * (data.Angle / 300.0) );
	int speed = (int)( data.Speed / 0.111 );
	int torque = (int) ( data.Torque * 1024.0 );

	buf[0] = data.TorqueON;
	buf[1] = data.LED;
	buf[2] = data.CW_ComplianceMargin;
	buf[3] = data.CCW_ComplianceMargin;
	buf[4] = data.CW_ComplianceSlope;
	buf[5] = data.CCW_ComplianceSlope;
	buf[6] = angle & 0xff;
	buf[7] = (angle >> 8) & 0xff;
	buf[8] = speed & 0xff;
	buf[9] = (speed >> 8) & 0xff;
	buf[10] = torque & 0xff;
	buf[11] = (torque >> 8) & 0xff;

}



/************************************************

        void initPacket(uchar *buf)

	概要：dynamixelに送る最初の2つのデータは決まっているので代入しておく

	引数：
              *buf・・・送るデータの配列
	
	戻り値：なし

*************************************************/
void CRANE::initPacket(uchar *buf)
{
	buf[0] = 0xff;
	buf[1] = 0xff;
}



/************************************************

        void RegWrite(int id, t_servoWrite data)

	概要：dynamixelのRegWriteでデータを送信する

	引数：
              id・・・モータのID
              data・・・データに代入する値 
	
	戻り値：なし

*************************************************/
void CRANE::RegWrite(int id, t_servoWrite data)
{
	uchar buf[19] = {0};
	
	initPacket(buf);
	buf[2] = id & 0xff;
	buf[3] = 15;
	buf[4] = 4;
	buf[5] = 24;

	WriteData2Bytes(buf + 6, data);
	buf[18] = calcRobotisCheckSum(buf, sizeof(buf));

	serialWrite(buf, sizeof(buf));
	CheckStatusPacket();
}



/************************************************

        void Action(void)

	概要：dynamixelのActionでデータを送信する

	引数：なし
	
	戻り値：なし

*************************************************/
void CRANE::Action(void)
{
	uchar buf[] = {0xff, 0xff, 254, 2, 5, 0};
	buf[sizeof(buf)-1] = calcRobotisCheckSum(buf, sizeof(buf));
	
	serialWrite(buf, sizeof(buf));
}





/************************************************

      void GetStatus(t_servo *servo)

      概要：Dynamixelの角度，速さ，トルクを読み込む

      引数：
           *servo・・・Dynamixelから受け取るデータを格納する変数と送るデータの変数

      戻り値：なし

*************************************************/
void CRANE::GetStatus(t_servo *servo)
{
	uchar buf[8] = { 0 };
	uchar recv[256] = { 0 };
	int tmp;
	t_servoRead *r = &(servo->read);

	initPacket(buf);
	buf[2] = servo->id;
	buf[3] = 4;
	buf[4] = 2;
	buf[5] = 36;
	buf[6] = 6;
	buf[7] = calcRobotisCheckSum(buf, sizeof(buf));

	serialWrite(buf, sizeof(buf));

	GetStatusPacket(recv);

	r->Angle = 300.0 * (recv[5] | (recv[6] << 8)) / 1024.0;

	tmp = (recv[7] + (recv[8] << 8)) & 1023;

	if (recv[8] & 4)
	{
		r->Speed = -0.111 * tmp;
	}
	else
	{
		r->Speed = 0.111 * tmp;
	}

	tmp = (recv[9] + (recv[10] << 8)) & 1023;
	if (recv[10] & 4)
	{
		r->Torque = -tmp / 1024.0;
	}
	else
	{
		r->Torque = tmp / 1024.0;
	}


}



/************************************************

       void getArmStatus(t_arm *arm)

       概要：アームすべてのDynamixelの角度，速さ，トルクを読み込む

       引数：
             *arm・・・Dynamixelから受け取るデータを格納する変数と送るデータの変数

       戻り値：なし

*************************************************/
void CRANE::getArmStatus(t_arm *arm)
{
	int i;
	for (i = 0; i < ARM_FREEDOM; i++)
	{
		GetStatus(arm->servo + i);
	}
}



/********************************************************************************/
/*                                  public関数                                  */
/********************************************************************************/


/************************************************

	int openSerialPort(const char *SERIAL_PORT)

	概要：シリアル通信を開始する

	引数：const char *SERIAL_PORT・・・ポート名
	
	戻り値：なし

*************************************************/
void CRANE::openSerialPort(const char *SERIAL_PORT)
{
	struct termios setting;
	
	fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY);
	if(fd < 0)
	{
		printf("Can't open port : %s\n",SERIAL_PORT);
		exit(-1);
	}
	
	setting.c_cflag = B1000000 | CS8 | CLOCAL | CREAD;
	
	setting.c_cc[VTIME] = 10;
	setting.c_cc[VMIN] = 10;
	setting.c_lflag = 0;
	setting.c_iflag = IGNPAR;
	setting.c_oflag = 0;	//RAW mode
	
	tcflush(fd, TCIOFLUSH);
	tcsetattr(fd, TCSANOW, &setting);
	
	return;
}


/************************************************

        void initServo(int id ,t_servo *servo)

       概要：サーボモーターに送るデータの変数を初期化する関数

       引数：
            id・・・サーボモーターのID
            *servo・・・各IDのDynamixelに送るデータの変数

       戻り値：なし

*************************************************/
void CRANE::initServo(int id, t_servo *servo)
{
	t_servoWrite *w = &(servo->write);

	servo->id = id;

	w->TorqueON = TRUE;
	w->LED = FALSE;
	w->CW_ComplianceMargin = 1;
	w->CCW_ComplianceMargin = 1;
	w->CW_ComplianceSlope = 32;
	w->CCW_ComplianceSlope = 32;
	w->Angle = 150;
	w->Speed = 20;
	w->Torque = 0.95;
}



/************************************************

       void initArm()

       概要：すべてのサーボモーターに送るデータの変数を初期化する関数

       引数：なし

       戻り値：なし

*************************************************/
void CRANE::initArm()
{
	int i;
	for(i = 0; i < ARM_FREEDOM; i++)
	{
	  initServo(i + 1, armdata.servo + i);
	}
}



/************************************************

       void setCRANEJointdata(double JointPos[])

       概要：JointPos[]の値をarmdata.servo[].write.Angleに書き込む

       引数：
            double JointPos[]・・・セットする角度データ

       戻り値：なし

*************************************************/
void CRANE::setCRANEJointdata(double JointPos[])
{
  armdata.servo[0].write.Angle = 150 + JointPos[0];
  armdata.servo[1].write.Angle = 240 - JointPos[1];
  armdata.servo[2].write.Angle = 150 + JointPos[2];
  armdata.servo[3].write.Angle = 150 + JointPos[3];
}


/************************************************

       void setCRANESpeeddata(double spdRatio)

       概要：spdRatioの値をarmdata.servo[].write.Speedに書き込む

       引数：
            double spdRatio・・・セットする速度データ

       戻り値：なし

*************************************************/
void CRANE::setCRANESpeeddata(double spdRatio)
{
  int i;
  for(i=0; i < ARM_FREEDOM; i++)
    {
      armdata.servo[i].write.Speed = spdRatio;
    }
}


/************************************************

       void setCRANECartesianLimit(Cartesian CartesianLimit)

       概要： CartesianLimitの値をCRANECartesianLimitに書き込む

       引数：
            Cartesian CartesianLimit・・・セットするリミットデータの構造体(詳しくはCrane.h)

       戻り値：なし

*************************************************/
void CRANE::setCRANECartesianLimit(Cartesian CartesianLimit)
{
  CRANECartesianLimit.x.Upper = CartesianLimit.x.Upper;
  CRANECartesianLimit.x.Lower = CartesianLimit.x.Lower;
  CRANECartesianLimit.y.Upper = CartesianLimit.y.Upper;
  CRANECartesianLimit.y.Lower = CartesianLimit.y.Lower;
  CRANECartesianLimit.z.Upper = CartesianLimit.z.Upper;
  CRANECartesianLimit.z.Lower = CartesianLimit.z.Lower;
}


/************************************************

       void setCRANEJointLimit(JLimit JointLimit[])

       概要： JointLimit[]の値をCRANEJointLimit[]に書き込む

       引数：
            JLimit JointLimit[]・・・セットするリミットデータの構造体(詳しくはCrane.h)

       戻り値：なし

*************************************************/
void CRANE::setCRANEJointLimit(JLimit JointLimit[])
{
  CRANEJointLimit[0].Upper = JointLimit[0].Upper;
  CRANEJointLimit[0].Lower = JointLimit[0].Lower;
  CRANEJointLimit[1].Upper = JointLimit[1].Upper;
  CRANEJointLimit[1].Lower = JointLimit[1].Lower;
  CRANEJointLimit[2].Upper = JointLimit[2].Upper;
  CRANEJointLimit[2].Lower = JointLimit[2].Lower;
  CRANEJointLimit[3].Upper = JointLimit[3].Upper;
  CRANEJointLimit[3].Lower = JointLimit[3].Lower;
}



/************************************************

      void ServoOnOff(int torque)

      概要：DynamixelのWrite_DataでサーボモーターのトルクのOnOffをする

      引数：
            int id・・・モーターのID
            int truque・・・トルク(1…ON,0…OFF)

      戻り値：なし

*************************************************/
void CRANE::ServoOnOff(int torque)
{
  int i = 0;
  uchar buf[8] = {0};
  for(i=0;i<ARM_FREEDOM;i++)
    {
      
      initPacket(buf);
      
      buf[2] = (i+1) & 0xff;
      buf[3] = 0x04;
      buf[4] = 0x03;
      buf[5] = 0x18;
      buf[6] = torque & 0xff;
      buf[7] = calcRobotisCheckSum(buf, sizeof(buf));
      
      serialWrite(buf, sizeof(buf));
      CheckStatusPacket();
    } 
}


/************************************************

      void getCRANEJointdata(double JointPos[])

      概要：クラス内の変数の角度データを入手する

      引数：
            double JointPos][]・・・入手した角度データを格納する変数

      戻り値：なし

*************************************************/
void CRANE::getCRANEJointdata(double JointPos[])
{

  getArmStatus(&armdata); 

  //アームが横に寝た状態からの角度
  JointPos[0] = -150 + armdata.servo[0].write.Angle;
  JointPos[1] =  240 - armdata.servo[1].write.Angle;
  JointPos[2] = -150 + armdata.servo[2].write.Angle;
  JointPos[3] = -150 + armdata.servo[3].write.Angle;
}


/************************************************

      void getCRANESpeeddata(double spdRatio)

      概要：クラス内の変数の速度データを入手する

      引数：
            double spdRatio・・・入手した角度データを格納する変数

      戻り値：なし

*************************************************/
void CRANE::getCRANESpeeddata(double spdRatio)
{

  getArmStatus(&armdata); 
  
  spdRatio = armdata.servo[0].write.Speed;
  
}


/************************************************

      void getCRANECartesianLimit(Cartesian CartesianLimit)

      概要：クラス内の変数の範囲リミットデータを入手する

      引数：
            Cartesian CartesianLimit・・・入手した範囲リミットデータを格納する変数

      戻り値：なし

*************************************************/
void CRANE::getCRANECartesianLimit(Cartesian CartesianLimit)
{
  CartesianLimit.x.Upper = CRANECartesianLimit.x.Upper;
  CartesianLimit.x.Lower = CRANECartesianLimit.x.Lower;
  CartesianLimit.y.Upper = CRANECartesianLimit.y.Upper;
  CartesianLimit.y.Lower = CRANECartesianLimit.y.Lower;
  CartesianLimit.z.Upper = CRANECartesianLimit.z.Upper;
  CartesianLimit.z.Lower = CRANECartesianLimit.z.Lower;

}


/************************************************

      void getCRANECartesianLimit(Cartesian CartesianLimit)

      概要：クラス内の変数の範囲リミットデータを入手する

      引数：
            Cartesian CartesianLimit・・・入手した範囲リミットデータを格納する変数

      戻り値：なし

*************************************************/
void CRANE::getCRANEJointLimit(JLimit JointLimit[])
{
  JointLimit[0].Upper = CRANEJointLimit[0].Upper;
  JointLimit[0].Lower = CRANEJointLimit[0].Lower;
  JointLimit[1].Upper = CRANEJointLimit[1].Upper;
  JointLimit[1].Lower = CRANEJointLimit[1].Lower;
  JointLimit[2].Upper = CRANEJointLimit[2].Upper;
  JointLimit[2].Lower = CRANEJointLimit[2].Lower;
  JointLimit[3].Upper = CRANEJointLimit[3].Upper;
  JointLimit[3].Lower = CRANEJointLimit[3].Lower;
}


/************************************************

      void ArmAction()

      概要：DynamixelのRegWrite-Actionでservo[].writeに書き込まれたデータをDynamixelに送信する

      引数：なし

      戻り値：なし

*************************************************/
void CRANE::ArmAction()
{
	int i;
	for (i = 0; i < ARM_FREEDOM; i++)
	{
		RegWrite(armdata.servo[i].id, armdata.servo[i].write);
	}
	Action();
}


/************************************************

      void CRANEcloseGripper()

      概要：CRANEのハンドを閉じる

      引数：なし

      戻り値：なし

*************************************************/
void CRANE::CRANEcloseGripper()
{
  armdata.servo[4].write.Angle = Hand_LimitMin;
  RegWrite(armdata.servo[ARM_FREEDOM - 1].id, armdata.servo[ARM_FREEDOM - 1].write);
  
  Action();
}



/************************************************

      void CRANEopenGripper()

      概要：CRANEのハンドを開く

      引数：なし

      戻り値：なし

*************************************************/
void CRANE::CRANEopenGripper()
{
  armdata.servo[4].write.Angle = Hand_LimitMax;
  RegWrite(armdata.servo[ARM_FREEDOM - 1].id, armdata.servo[ARM_FREEDOM - 1].write);
  
  Action();
}


/************************************************

      void CRANEopenGripper()

      概要：CRANEのハンド指定した開度でを開く

      引数：double angleRatio・・・開度

      戻り値：なし

*************************************************/
void CRANE::CRANEmoveGripper(double angleRatio)
{
  armdata.servo[4].write.Angle = (Hand_LimitMax-Hand_LimitMin)*(angleRatio*0.01)+Hand_LimitMin;
  RegWrite(armdata.servo[ARM_FREEDOM - 1].id, armdata.servo[ARM_FREEDOM - 1].write);

  Action(); 
}


/************************************************

       kinematics(double x, double y, double z, double JointPos[])

       概要：アームの逆運動学を計算する

       引数：
            double x・・・x座標
            double y・・・y座標
            double z・・・z座標     
            double JointPos[]・・・計算した角度を格納する変数  
    
       戻り値：関節角度

*************************************************/
void CRANE::kinematics(double x, double y, double z, double JointPos[])
{
	double x3;
	double y3;
	double z3;
	double theta1;
	double theta2;
	double theta3;
	double theta4;
	int i;
	double sentan = 0;
	double sentan_rad;
	double theta3_value;
	double deg;
	double rad;


	deg = M_PI / 180;  //degをradへ
	rad = 180 / M_PI;  //radをdegへ

	//座標原点合わせ
	x = x - 14.5;
	z = z - 45.4;

	if (x == 0)
		theta1 = 0;
	else
		theta1 = atan2(y, x);


	for (i = 0; i < 92; i++)
	{
		sentan_rad = sentan*deg;
		x3 = x - r3*cos(sentan_rad)*cos(theta1);
		y3 = y - r3*cos(sentan_rad)*sin(theta1);
		z3 = z - r3*sin(sentan_rad);

		theta3_value = ((x3*cos(theta1) + y3*sin(theta1))*(x3*cos(theta1) + y3*sin(theta1)) + z3*z3 - r2*r2 - r1*r1) / (2 * r1*r2);
		theta3 = acos(theta3_value);

		if (theta3 > 0)
		{
			//printf("theta3が+は綺麗じゃない\n");
			theta3 = -theta3;
		}


		if (i > 90)
		{
			//printf("この位置に移動できません\nquit program\n");
			//exit();
		}
		else if (theta3 != theta3)
		{
			//printf("sentan = %f\n", sentan);
			//printf("この位置に移動できません\n");
			sentan++;
		}

		else
		{
			//printf("先端角度は%f\n", sentan);
			//printf("x3=%f\n", x3);
			//printf("y3=%f\n", y3);
			//printf("angle2=%f\n", angle2);
			break;
		}
	}

	if (z >= 0)
	{
		//θ2の計算
		double alfa;
		alfa = atan((-r2*sin(theta3)) / (r1 + r2*cos(theta3)));

		theta2 = acos(sqrt(x3*x3 + y3*y3) / sqrt((r1 + r2*cos(theta3))*(r1 + r2*cos(theta3)) + (r2*sin(theta3))*(r2*sin(theta3)))) + alfa;

		if (theta2 < 0)
		{
			//printf("theta2がマイナス\n");
			theta3 = -theta3;
			alfa = atan((-r2*sin(theta3)) / (r1 + r2*cos(theta3)));
			theta2 = acos(sqrt(x3*x3 + y3*y3) / sqrt((r1 + r2*cos(theta3))*(r1 + r2*cos(theta3)) + (r2*sin(theta3))*(r2*sin(theta3)))) + alfa;
		
		}
		double kenzanx3;
		kenzanx3 = cos(theta1)*(r1*cos(theta2) + r2*cos((theta3 + theta2)));
		double kenzany3;
		kenzany3 = sin(theta1)*(r1*cos(theta2) + r2*cos((theta3 + theta2)));

		if (x3 - kenzanx3 > 1 || x3 - kenzanx3 < -1|| y3 - kenzany3 > 1 || y3 - kenzany3 < -1)
		{
	theta2 = acos(-sqrt(x3*x3 + y3*y3) / sqrt((r1 + r2*cos(theta3))*(r1 + r2*cos(theta3)) + (r2*sin(theta3))*(r2*sin(theta3)))) + alfa;
		}
	}

	else
	{
		//θ2の計算
		double alfa;
		alfa = atan((-r2*sin(theta3)) / (r1 + r2*cos(theta3)));
		theta2 = -acos(sqrt(x3*x3 + y3*y3) / sqrt((r1 + r2*cos(theta3))*(r1 + r2*cos(theta3)) + (r2*sin(theta3))*(r2*sin(theta3)))) + alfa;
	}



	theta4 = sentan_rad - theta2 - theta3;

	//第一関節AX-12Aの可動範囲外
	if ((theta1 > 150*deg && theta1 <= 180*deg) || (theta1 < -150*deg && theta1 >= -180*deg))
	{
		theta1 = theta1 - M_PI;
		theta2 = M_PI - theta2;
		theta3 = -theta3;
		theta4 = -theta4;
	}

	JointPos[0] = theta1*rad;
	JointPos[1] = theta2*rad;
	JointPos[2] = theta3*rad;
	JointPos[3] = theta4*rad;

}

/************************************************

	int CartesianLimitJudgement( double x , double y , double z )
	
	概要：Catesianソフトリミットの判定を行う

	引数：
		double x・・・x[mm]
		double y・・・y[mm]
		double z・・・z[mm]

	戻り値：Cartesianソフトリミットを満たしていればTRUE、そうでなければFALSE

*************************************************/
int CRANE::CartesianLimitJudgement( double x , double y , double z )
{
  if(( x > CRANECartesianLimit.x.Upper )||
     ( x < CRANECartesianLimit.x.Lower )||
     ( y > CRANECartesianLimit.y.Upper )||
     ( y < CRANECartesianLimit.y.Lower )||
     ( z > CRANECartesianLimit.z.Upper )||
     ( z < CRANECartesianLimit.z.Lower )
     ){
    return FALSE;
  }
  
    return TRUE;
}

/************************************************

	int JointLimitJudgement()
	
	概要：Jointソフトリミットの判定を行う

	引数：なし

	戻り値：Jointソフトリミットを満たしていればTRUE、そうでなければFALSE

*************************************************/
int CRANE::JointLimitJudgement()
{
  
  for(int i=0;i<ARM_FREEDOM-1;i++){
    if(( armdata.servo[i].write.Angle > CRANEJointLimit[i].Upper )||
       ( armdata.servo[i].write.Angle < CRANEJointLimit[i].Lower ))
      {
	std::cout<<"ERROR : Wrong Value"<<std::endl<<std::endl;
	return FALSE;
      }
  }
 
    return TRUE;
}


/************************************************

	int CRANELimitJudgement(double x, double y, double z)
	
	概要：CRANE+リミットの判定を行う

	引数：先端座標値
		double x・・・x[mm]
                double y・・・y[mm]
		double z・・・z[mm]

	戻り値：CRANE+リミットを満たしていればTRUE、そうでなければFALSE

*************************************************/
int CRANE::CRANELimitJudgement(double x, double y, double z)
{

  x = x - 14.5;
  z = z - 45.4;

  if(sqrt(x*x+z*z+y*y)>314.5)
    {
      return FALSE;
    }
  else if(sqrt(x*x+z*z+y*y) < 200)
    {
      return FALSE;
    }
  else
    return TRUE;

}
