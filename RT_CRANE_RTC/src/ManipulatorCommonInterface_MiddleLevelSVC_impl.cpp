// -*-C++-*-
/*!
 * @file  ManipulatorCommonInterface_MiddleLevelSVC_impl.cpp
 * @brief Service implementation code of ManipulatorCommonInterface_MiddleLevel.idl
 *
 */

#include "ManipulatorCommonInterface_MiddleLevelSVC_impl.h"
#include "Crane.h"
#include "returnID.h"

double HomeMotorPosition[4];
/*
 * Example implementational code for IDL interface JARA_ARM::ManipulatorCommonInterface_Middle
 */
JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl()
{
  // Please add extra constructor code here.
}


JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::~JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::closeGripper()
{
  std::cout << "closeGripper" << std::endl;
  crane.CRANEcloseGripper();
  std::cout<<"Success"<<std::endl<<std::endl;
  RETURNID_OK;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getBaseOffset(JARA_ARM::HgMatrix offset)
{
  std::cout<<"getBaseOffset"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getFeedbackPosCartesian(JARA_ARM::CarPosWithElbow& pos)
{
  double x;
  double y;
  double z;
  double Rz;
  double deg;
  double rad;
  double JointPos[ARM_FREEDOM-1];

  deg = M_PI / 180;  //degをradへ
  rad = 180/M_PI;    //radをdegへ	

  std::cout << "getFeedbackPosCartesian" << std::endl;

  //モーター関節値の読み込み
  crane.getCRANEJointdata(JointPos);

  //関節の現在位置の計算(順運動学)
  x = cos(JointPos[0]*deg) * (r1*cos(JointPos[1]*deg) +r2*cos((JointPos[1] + JointPos[2])*deg) + r3*cos((JointPos[1] + JointPos[2] + JointPos[3])*deg))+14.5;//[mm]
  y = sin(JointPos[0]*deg) * (r1*cos(JointPos[1]*deg) +r2*cos((JointPos[1] + JointPos[2])*deg) + r3*cos((JointPos[1] + JointPos[2] + JointPos[3])*deg));//[mm]
  z =(r1*sin(JointPos[1]*deg) +r2*sin((JointPos[1] + JointPos[2])*deg) + r3*sin((JointPos[1] + JointPos[2] + JointPos[3])*deg))+45.4;//[mm]
  Rz = (JointPos[1] + JointPos[2] + JointPos[3])*deg;//[rad]



    
  pos.carPos[0][0]=cos(Rz);
  pos.carPos[0][1]=-sin(Rz);
  pos.carPos[0][2]=0.0;
  pos.carPos[0][3]=(x);//x[mm]
  
  pos.carPos[1][0]=sin(Rz);
  pos.carPos[1][1]=cos(Rz);
  pos.carPos[1][2]=0.0;
  pos.carPos[1][3]=(y);//y[mm]
  
  pos.carPos[2][0]=0.0;
  pos.carPos[2][1]=0.0;
  pos.carPos[2][2]=1.0;
  pos.carPos[2][3]=(z);//z[mm]

  std::cout<<" x  : "<< pos.carPos[0][3] << "[mm]" <<std::endl;
  std::cout<<" y  : "<< pos.carPos[1][3] << "[mm]" <<std::endl;
  std::cout<<" z  : "<< pos.carPos[2][3] << "[mm]" <<std::endl;
  std::cout<<" Rz : "<< Rz*rad << "[deg]" << std::endl;

  std::cout<<"Success"<<std::endl<<std::endl;
  
  RETURNID_OK;

}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getMaxSpeedCartesian(JARA_ARM::CartesianSpeed& speed)
{
  std::cout<<"GetMaxSpeedCartesian"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getMaxSpeedJoint(JARA_ARM::DoubleSeq_out speed)
{
  speed = new JARA_ARM::DoubleSeq;
  speed->length(1); 
  std::cout<<"GetMaxSpeedJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getMinAccelTimeCartesian(::CORBA::Double& aclTime)
{
  std::cout<<"GetMinAccelTimeJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getMinAccelTimeJoint(::CORBA::Double& aclTime)
{
  std::cout<<"GetMinAccelTimeJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}


JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getSoftLimitCartesian(JARA_ARM::LimitValue& xLimit, JARA_ARM::LimitValue& yLimit, JARA_ARM::LimitValue& zLimit)
{
  std::cout<<"GetSoftLimitCartesian"<<std::endl;
  Cartesian CartesianLimit;
  
  crane.getCRANECartesianLimit(CartesianLimit);
  xLimit.upper = CartesianLimit.x.Upper;//[mm](ロボット座標系)
  xLimit.lower = CartesianLimit.x.Lower;
  yLimit.upper = CartesianLimit.y.Upper;
  yLimit.lower = CartesianLimit.y.Lower;
  zLimit.upper = CartesianLimit.z.Upper;
  zLimit.lower = CartesianLimit.z.Lower;
  
  std::cout << "xLimit.upper : " << xLimit.upper << std::endl;
  std::cout << "xLimit.lower : " << xLimit.lower << std::endl;
  std::cout << "yLimit.upper : " << yLimit.upper << std::endl;
  std::cout << "yLimit.lower : " << yLimit.lower << std::endl;
  std::cout << "zLimit.upper : " << zLimit.upper << std::endl;
  std::cout << "zLimit.lower : " << zLimit.lower << std::endl;

  std::cout<<"Success"<<std::endl<<std::endl;
  RETURNID_OK;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::moveGripper(JARA_ARM::ULONG angleRatio)
{
  std::cout << "moveGripper" << std::endl;
  double move;

  move = (double)angleRatio;

  if(angleRatio>0 && angleRatio<=100){
    crane.CRANEmoveGripper(move);
  }
  else{
    std::cout << "ERROR : angleRatio Wrong Value" << std::endl;
    RETURNID_VALUE_ERR;
  }
  std::cout<<"Success"<<std::endl<<std::endl;

  RETURNID_OK;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::moveLinearCartesianAbs(const JARA_ARM::CarPosWithElbow& carPoint)
{
  //double rad = 180/M_PI; //ラジアンを度数
  int Judge;
  double CRANEJointPos[ARM_FREEDOM-1];
  
  std::cout << "moveLinearCartesianAbs" << std::endl;

  //Cartesianソフトリミット判定
  Judge = crane.CartesianLimitJudgement(carPoint.carPos[0][3],carPoint.carPos[1][3],carPoint.carPos[2][3]);

  if(Judge != TRUE){
    std::cout<<"ERROR : Cartesian Soft Limit Over"<<std::endl<<std::endl;
    RETURNID_NG;
  }

  //CRANEソフトリミット判定
  Judge = crane.CRANELimitJudgement(carPoint.carPos[0][3],carPoint.carPos[1][3],carPoint.carPos[2][3]);
  if(Judge != TRUE){
    std::cout<<"ERROR : CRANE Limit Over"<<std::endl<<std::endl;
    RETURNID_NG;
  }

  //逆運動学  JointPosに計算角度が格納される
  crane.kinematics(carPoint.carPos[0][3],carPoint.carPos[1][3],carPoint.carPos[2][3],CRANEJointPos);
  
  //角度データセット
  crane.setCRANEJointdata(CRANEJointPos);

  //Jointソフトリミット判定
  Judge = crane.JointLimitJudgement();
  if(Judge != TRUE){
    std::cout<<"ERROR : Joint Soft Limit Over"<<std::endl<<std::endl;
    RETURNID_NG;
  }

  crane.ArmAction();
  
  std::cout<<"Success"<<std::endl<<std::endl;
  
  RETURNID_OK;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::moveLinearCartesianRel(const JARA_ARM::CarPosWithElbow& carPoint)
{
  std::cout<<"moveLinearCartesianRel"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::movePTPCartesianAbs(const JARA_ARM::CarPosWithElbow& carPoint)
{
  std::cout<<"movePTPCartesianAbs"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::movePTPCartesianRel(const JARA_ARM::CarPosWithElbow& carPoint)
{
  std::cout<<"movePTPCartesianRel"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::movePTPJointAbs(const JARA_ARM::JointPos& jointPoints)
{
  std::cout << "movePTPJointAbs" << std::endl;
  int Judge;
  double CRANEJointPos[ARM_FREEDOM-1];

  for(int i=0;i<4;i++){
  std::cout << "JointPoint["<<i<<"] = " << jointPoints[i] <<std::endl; 
  }

  CRANEJointPos[0] = jointPoints[0];
  CRANEJointPos[1] = 90 + jointPoints[1];
  CRANEJointPos[2] = jointPoints[2];
  CRANEJointPos[3] = jointPoints[3];

  Judge = crane.JointLimitJudgement();
  if(Judge != TRUE){
    std::cout<<"ERROR : Joint Soft Limit Over"<<std::endl<<std::endl;
    RETURNID_NG;
  }
  crane.setCRANEJointdata(CRANEJointPos);
  crane.ArmAction();
  
  std::cout<<"Success"<<std::endl<<std::endl;
  
  RETURNID_OK;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::movePTPJointRel(const JARA_ARM::JointPos& jointPoints)
{
  std::cout<<"movePTPJointRel"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::openGripper()
{
  std::cout << "OpenGripper" << std::endl;
  crane.CRANEopenGripper();
  std::cout<<"Success"<<std::endl<<std::endl;
  RETURNID_OK;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::pause()
{
  std::cout<<"pause"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::resume()
{
  std::cout<<"resume"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::stop()
{
  std::cout<<"stop"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl; 
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setAccelTimeCartesian(::CORBA::Double aclTime)
{
  std::cout<<"setAccelTimeCartesian"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setAccelTimeJoint(::CORBA::Double aclTime)
{
  std::cout<<"setAccelTimeJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setBaseOffset(const JARA_ARM::HgMatrix offset)
{
  std::cout<<"setBaseOffset"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setControlPointOffset(const JARA_ARM::HgMatrix offset)
{
  std::cout<<"setControlPointOffset"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setMaxSpeedCartesian(const JARA_ARM::CartesianSpeed& speed)
{
  std::cout<<"setMaxSpeedCartesian"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setMaxSpeedJoint(const JARA_ARM::DoubleSeq& speed)
{
  std::cout<<"setMaxSpeedJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setMinAccelTimeCartesian(::CORBA::Double aclTime)
{
  std::cout<<"setMinAccelTimeCartesian"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setMinAccelTimeJoint(::CORBA::Double aclTime)
{
  std::cout<<"setMinAccelTimeJoint"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setSoftLimitCartesian(const JARA_ARM::LimitValue& xLimit, const JARA_ARM::LimitValue& yLimit, const JARA_ARM::LimitValue& zLimit)
{
  std::cout<<"SetSoftLimitCartesian"<<std::endl;
  Cartesian CartesianLimit;
  
  if((xLimit.upper <= X_LimitMax) && 
     (xLimit.lower >= X_LimitMin) &&
     (yLimit.upper <= Y_LimitMax) && 
     (yLimit.lower >= Y_LimitMin) &&
     (zLimit.upper <= Z_LimitMax) && 
     (zLimit.lower >= Z_LimitMin) 
     ){
    CartesianLimit.x.Upper = xLimit.upper;
    CartesianLimit.x.Lower = xLimit.lower;
    CartesianLimit.y.Upper = yLimit.upper;
    CartesianLimit.y.Lower = yLimit.lower;
    CartesianLimit.z.Upper = zLimit.upper;
    CartesianLimit.z.Lower = zLimit.lower;
    crane.setCRANECartesianLimit(CartesianLimit);
    }
  else{
    std::cout<<"ERROR : Wrong Value"<<std::endl<<std::endl;
    RETURNID_VALUE_ERR;
  }
  
  std::cout<<"Success"<<std::endl<<std::endl;
  
  RETURNID_OK;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setSpeedCartesian(JARA_ARM::ULONG spdRatio)
{
  std::cout<<"setSpeedCartesian"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setSpeedJoint(JARA_ARM::ULONG spdRatio)
{
  std::cout << "SetSpeedJoint" << std::endl;
  std::cout << "setSpeed = " << spdRatio << "%" << std::endl;
  double speed;
  speed = (double)spdRatio; 
  
  if (spdRatio >= 1 && spdRatio <= 100){
    crane.setCRANESpeeddata(speed);
  }
  else{
    std::cout << "ERROR : Wrong Value" << std::endl << std::endl;
    RETURNID_VALUE_ERR;
  }
  
  std::cout << "Success" << std::endl << std::endl;
  
  RETURNID_OK;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::moveCircularCartesianAbs(const JARA_ARM::CarPosWithElbow& carPointR, const JARA_ARM::CarPosWithElbow& carPointT)
{
  std::cout<<"moveCircularCartesianAbs"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::moveCircularCartesianRel(const JARA_ARM::CarPosWithElbow& carPointR, const JARA_ARM::CarPosWithElbow& carPointT)
{
  std::cout<<"moveCircularCartesianRel"<<std::endl;
  std::cout<<"ERROR : コマンド未実装"<<std::endl<<std::endl;
  RETURNID_NOT_IMPLEMENTED;
}


JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setHome(const JARA_ARM::JointPos& jointPoint)
{
  
  std::cout<<"SetHome"<<std::endl;
  
  HomeMotorPosition[0] = (short)(jointPoint[0]);
  HomeMotorPosition[1] = 90 + (short)(jointPoint[1]);
  HomeMotorPosition[2] = (short)(jointPoint[2]);
  HomeMotorPosition[3] = (short)(jointPoint[3]);
  
  std::cout<<"Success"<<std::endl<<std::endl;
  
  RETURNID_OK;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getHome(JARA_ARM::JointPos_out jointPoint)
{
  std::cout<<"GetHome"<<std::endl;
  
  jointPoint=new JARA_ARM::JointPos;
  jointPoint->length(ARM_FREEDOM);
  
  (*jointPoint)[0]=HomeMotorPosition[0];
  (*jointPoint)[1]=HomeMotorPosition[1];
  (*jointPoint)[2]=HomeMotorPosition[2];
  (*jointPoint)[3]=HomeMotorPosition[3];
  
  std::cout<<"Success"<<std::endl<<std::endl;
  
  RETURNID_OK;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::goHome()
{
  std::cout<<"GoHome"<<std::endl;
  crane.setCRANEJointdata(HomeMotorPosition);
  crane.ArmAction();

  std::cout<<"Success"<<std::endl<<std::endl;
  
  RETURNID_OK;
}


// End of example implementational code



