// -*-C++-*-
/*!
 * @file  ManipulatorCommonInterface_CommonSVC_impl.cpp
 * @brief Service implementation code of ManipulatorCommonInterface_Common.idl
 *
 */

#include "ManipulatorCommonInterface_CommonSVC_impl.h"
#include "ChoreonoidCRANEControllerRTC.h"
#include "ChoreonoidControl.h"
#include "Crane.h"
#include "defreturnid.h"

/*
 * Example implementational code for IDL interface JARA_ARM::ManipulatorCommonInterface_Common
 */
JARA_ARM_ManipulatorCommonInterface_CommonSVC_impl::JARA_ARM_ManipulatorCommonInterface_CommonSVC_impl()
{
  // Please add extra constructor code here.
}


JARA_ARM_ManipulatorCommonInterface_CommonSVC_impl::~JARA_ARM_ManipulatorCommonInterface_CommonSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_CommonSVC_impl::clearAlarms()
{
  std::cout << "ClearAlarms" << std::endl;
  std::cout << "ERROR : コマンド未実装" << std::endl << std::endl;
  
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_CommonSVC_impl::getActiveAlarm(JARA_ARM::AlarmSeq_out alarms)
{
  alarms=new JARA_ARM::AlarmSeq;
  alarms->length(3);
  std::cout << "GetActiveAlarm" << std::endl;
  std::cout << "ERROR : コマンド未実装" << std::endl << std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_CommonSVC_impl::getFeedbackPosJoint(JARA_ARM::JointPos_out pos)
{
  std::cout << "GetFeedbackPosJoint" << std::endl;
  
  pos = new JARA_ARM::JointPos;
  pos->length(ARM_FREEDOM);
  
  if(c_Mode==1||c_Mode==2)
    {
      double CRANEJointPos[ARM_FREEDOM-1];
      crane.getCRANEJointdata(CRANEJointPos);
      std::cout << "実機の角度" << std::endl;
      for(int i = 0;i<ARM_FREEDOM;i++)
	{
	  pos[i] = CRANEJointPos[i];
	  if(i!=4)//グリッパは表示しない
	    std::cout << "pos["<<i<<"] = " << pos[i] << "[°]" << std::endl;
	}
    }
  std::cout << "Success" << std::endl << std::endl;

  RETURNID_OK;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_CommonSVC_impl::getManipInfo(JARA_ARM::ManipInfo_out mInfo)
{
  std::cout << "GetManipInfo" << std::endl;
  
  mInfo = new JARA_ARM::ManipInfo;
  mInfo->manufactur = "Hardware：RT CORPORATION  Software：Meijo University robot systems design laboratory";
  mInfo->type = "CRANE+";
  mInfo->cmdCycle = 30;
  mInfo->axisNum = 4;
  mInfo->isGripper = true;
  
  
  std::cout << " manufactur : " << mInfo->manufactur << std::endl;
  std::cout << " type       : " << mInfo->type << std::endl;
  std::cout << " axisNum    : " << mInfo->axisNum << std::endl;
  std::cout << " cmdCycle   : " << mInfo->cmdCycle << std::endl;
  std::cout << " isGripper  : " << mInfo->isGripper << std::endl;
  
  std::cout << "Success" << std::endl << std::endl;
  
  RETURNID_OK;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_CommonSVC_impl::getSoftLimitJoint(JARA_ARM::LimitSeq_out softLimit)
{
  std::cout<<"getSoftLimitJoint"<<std::endl;
  

  softLimit=new JARA_ARM::LimitSeq;
  softLimit->length(ARM_FREEDOM);
  
  JLimit JointLimit[ARM_FREEDOM-1];
  for(int i=0;i<ARM_FREEDOM-1;i++){
    crane.getCRANEJointLimit(JointLimit);
      }
  
  for(int i=0;i<=3;i++){
    std::cout << "JointLimit["<<i<<"].Upper =" << JointLimit[i].Upper << std::endl; 
    std::cout << "JointLimit["<<i<<"].Lower =" << JointLimit[i].Lower << std::endl;  
  }
  
  (*softLimit)[0].upper=(double)JointLimit[0].Upper;
  (*softLimit)[0].lower=(double)JointLimit[0].Lower;
  (*softLimit)[1].upper=(double)JointLimit[1].Upper;
  (*softLimit)[1].lower=(double)JointLimit[1].Lower;
  (*softLimit)[2].upper=(double)JointLimit[2].Upper;
  (*softLimit)[2].lower=(double)JointLimit[2].Lower;
  (*softLimit)[3].upper=(double)JointLimit[3].Upper;
  (*softLimit)[3].lower=(double)JointLimit[3].Lower;


  std::cout<<"Success"<<std::endl<<std::endl;
  RETURNID_OK;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_CommonSVC_impl::getState(JARA_ARM::ULONG& state)
{
  std::cout << "getState" << std::endl;
  std::cout << "コマンド未実装" << std::endl << std::endl;
  RETURNID_NOT_IMPLEMENTED;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_CommonSVC_impl::servoOFF()
{

  int torque = 0;
  std::cout<<"ServoOFF (SERVO_OFF)"<<std::endl;  
  
  if(c_Mode==1||c_Mode==2)
    crane.ServoOnOff(torque);

  std::cout<<"Success"<<std::endl<<std::endl;
  simcode = 102;
  RETURNID_OK;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_CommonSVC_impl::servoON()
{

  int torque = 1;
  std::cout<<"ServoON (SERVO_ON)"<<std::endl;
  if(c_Mode==1||c_Mode==2)
    crane.ServoOnOff(torque);
  
  std::cout<<"Success"<<std::endl<<std::endl;
  simcode = 101;
  RETURNID_OK;
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_CommonSVC_impl::setSoftLimitJoint(const JARA_ARM::LimitSeq& softLimit)
{

  JLimit JointLimit[ARM_FREEDOM-1];

  std::cout<<"SetSoftLimitJoint"<<std::endl;

  if((Angle1_LimitMax>=softLimit[0].upper)&&
     (Angle1_LimitMin<=softLimit[0].lower)&&
     (Angle2_LimitMax>=softLimit[1].upper)&&
     (Angle2_LimitMin<=softLimit[1].lower)&&
     (Angle3_LimitMax>=softLimit[2].upper)&&
     (Angle3_LimitMin<=softLimit[2].lower)&&
     (Angle4_LimitMax>=softLimit[3].upper)&&
     (Angle4_LimitMin<=softLimit[3].lower))
    {   
      for(int i=0;i<ARM_FREEDOM-1;i++){
        JointLimit[i].Upper = softLimit[i].upper;
	JointLimit[i].Lower = softLimit[i].lower;
      }	
      crane.setCRANEJointLimit(JointLimit); 
    }
  else 
    {
      std::cout<<"ERROR : Wrong Value"<<std::endl<<std::endl;
      RETURNID_VALUE_ERR;
    }

  std::cout<<"Success"<<std::endl<<std::endl;  
  RETURNID_OK;
}



// End of example implementational code



