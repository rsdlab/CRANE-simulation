// -*-C++-*-
/*!
 * @file  ManipulatorCommonInterface_MiddleLevelSVC_impl.cpp
 * @brief Service implementation code of ManipulatorCommonInterface_MiddleLevel.idl
 *
 */

#include "ManipulatorCommonInterface_MiddleLevelSVC_impl.h"
#include "Craneplus.h"
#include "returnID.h"

double HomeMotorPosition[4];
double spdRatio_Middle;

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
	std::cout << "Success" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::OK, "�I�y���[�V�����𐳏�Ɏ󂯕t��");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getBaseOffset(JARA_ARM::HgMatrix offset)
{
	std::cout << "getBaseOffset" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getFeedbackPosCartesian(JARA_ARM::CarPosWithElbow& pos)
{
	double x;
	double y;
	double z;
	double Rz;
	double deg;
	double rad;
	double JointPos[ARM_FREEDOM - 1];

	deg = M_PI / 180;  //deg��rad��
	rad = 180 / M_PI;    //rad��deg��	

	std::cout << "getFeedbackPosCartesian" << std::endl;

	//���[�^�[�֐ߒl�̓ǂݍ���
	crane.getCRANEJointdata(JointPos);

	//�֐߂̌��݈ʒu�̌v�Z(���^���w)
	x = cos(JointPos[0] * deg) * (r1*cos((90 - JointPos[1])*deg) + r2*cos((90 - JointPos[1] - JointPos[2])*deg) + r3*cos((90 - JointPos[1] - JointPos[2] - JointPos[3])*deg)) + 14.5;//[mm]
	y = sin(JointPos[0] * deg) * (r1*cos((90 - JointPos[1])*deg) + r2*cos((90 - JointPos[1] - JointPos[2])*deg) + r3*cos((90 - JointPos[1] - JointPos[2] - JointPos[3])*deg));//[mm]
	z = (r1*sin((90 - JointPos[1])*deg) + r2*sin((90 - JointPos[1] - JointPos[2])*deg) + r3*sin((90 - JointPos[1] - JointPos[2] - JointPos[3])*deg)) + 45.4;//[mm]
	Rz = (90 - JointPos[1] - JointPos[2] - JointPos[3])*deg;//[rad]



	pos.carPos[0][0] = cos(Rz);
	pos.carPos[0][1] = -sin(Rz);
	pos.carPos[0][2] = 0.0;
	pos.carPos[0][3] = (x);//x[mm]

	pos.carPos[1][0] = sin(Rz);
	pos.carPos[1][1] = cos(Rz);
	pos.carPos[1][2] = 0.0;
	pos.carPos[1][3] = (y);//y[mm]

	pos.carPos[2][0] = 0.0;
	pos.carPos[2][1] = 0.0;
	pos.carPos[2][2] = 1.0;
	pos.carPos[2][3] = (z);//z[mm]

	std::cout << " x  : " << pos.carPos[0][3] << "[mm]" << std::endl;
	std::cout << " y  : " << pos.carPos[1][3] << "[mm]" << std::endl;
	std::cout << " z  : " << pos.carPos[2][3] << "[mm]" << std::endl;
	std::cout << " Rz : " << Rz*rad << "[deg]" << std::endl;

	std::cout << "Success" << std::endl << std::endl;

	return RETURN_CODE(JARA_ARM::OK, "�I�y���[�V�����𐳏�Ɏ󂯕t��");

}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getMaxSpeedCartesian(JARA_ARM::CartesianSpeed& speed)
{
	std::cout << "GetMaxSpeedCartesian" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getMaxSpeedJoint(JARA_ARM::DoubleSeq_out speed)
{
	speed = new JARA_ARM::DoubleSeq;
	speed->length(1);
	std::cout << "GetMaxSpeedJoint" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getMinAccelTimeCartesian(::CORBA::Double& aclTime)
{
	std::cout << "GetMinAccelTimeJoint" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getMinAccelTimeJoint(::CORBA::Double& aclTime)
{
	std::cout << "GetMinAccelTimeJoint" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}


JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getSoftLimitCartesian(JARA_ARM::LimitValue& xLimit, JARA_ARM::LimitValue& yLimit, JARA_ARM::LimitValue& zLimit)
{
	std::cout << "GetSoftLimitCartesian" << std::endl;
	Cartesian CartesianLimit;

	crane.getCRANECartesianLimit(CartesianLimit);
	xLimit.upper = CartesianLimit.x.Upper;//[mm](���{�b�g���W�n)
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

	std::cout << "Success" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::OK, "�I�y���[�V�����𐳏�Ɏ󂯕t��");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::moveGripper(JARA_ARM::ULONG angleRatio)
{
	std::cout << "moveGripper" << std::endl;
	double move;

	move = (double)angleRatio;

	if (angleRatio>0 && angleRatio <= 100){
		crane.CRANEmoveGripper(move);
	}
	else{
		std::cout << "ERROR : angleRatio Wrong Value" << std::endl;
		return RETURN_CODE(JARA_ARM::VALUE_ERR, "�������s��");
	}
	std::cout << "Success" << std::endl << std::endl;

	return RETURN_CODE(JARA_ARM::OK, "�I�y���[�V�����𐳏�Ɏ󂯕t��");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::moveLinearCartesianAbs(const JARA_ARM::CarPosWithElbow& carPoint)
{
	std::cout << "moveLinearCartesianAbs" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::moveLinearCartesianRel(const JARA_ARM::CarPosWithElbow& carPoint)
{
	std::cout << "moveLinearCartesianRel" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::movePTPCartesianAbs(const JARA_ARM::CarPosWithElbow& carPoint)
{
	int i = 0, idm = 0, ids = 0, idt = 0, idf = 0;
	double setfabs = 0;
	int Judge;
	double CRANEJointPos[ARM_FREEDOM - 1];   //���̐�Βl
	double nowJointPos[ARM_FREEDOM - 1];     //���ݒl
	double targetJointPos[ARM_FREEDOM - 1];  //�ڕW�l
	double difference[ARM_FREEDOM - 1];      //���ݒl�ƖڕW�l�̍�
	double max = 0;      //���̏��ʕt��
	double second = 0;
	double third = 0;
	double fourth = 0;

	std::cout << "moveLinearCartesianAbs" << std::endl;

	//Cartesian�\�t�g���~�b�g����
	Judge = crane.CartesianLimitJudgement(carPoint.carPos[0][3], carPoint.carPos[1][3], carPoint.carPos[2][3]);

	if (Judge != true){
		std::cout << "ERROR : Cartesian Soft Limit Over" << std::endl << std::endl;
		return RETURN_CODE(JARA_ARM::NG, "�I�y���[�V��������");
	}

	//CRANE�\�t�g���~�b�g����
	Judge = crane.CRANELimitJudgement(carPoint.carPos[0][3], carPoint.carPos[1][3], carPoint.carPos[2][3]);
	if (Judge != true){
		std::cout << "ERROR : CRANE Limit Over" << std::endl << std::endl;
		return RETURN_CODE(JARA_ARM::NG, "�I�y���[�V��������");
	}

	crane.getCRANEJointdata(nowJointPos);

	//�t�^���w  JointPos�Ɍv�Z�p�x���i�[�����
	crane.kinematics(carPoint.carPos[0][3], carPoint.carPos[1][3], carPoint.carPos[2][3], targetJointPos);
	//�ڕW�l�ƌ��ݒn�̍������
	for (int h = 0; h<ARM_FREEDOM - 1; h++){
		difference[h] = targetJointPos[h] - nowJointPos[h];
		setfabs = difference[h];
		CRANEJointPos[h] = fabs(setfabs);   //��Βl
		//std::cout << "CRANEJointPos[h] = " << CRANEJointPos[h] << std::endl;
	}


	//�ڕW�l�ƌ��ݒn�̍��ɂ���Ċ֐ߑ��x��ς���
	//��ԍ����傫��Servoid�����߂�
	max = CRANEJointPos[0];
	i = 0;
	idm = i + 1;
	for (i = 1; i<ARM_FREEDOM - 1; i++){
		if (max < CRANEJointPos[i]){
			fourth = third;
			third = second;
			second = max;
			max = CRANEJointPos[i];
			idf = idt;
			idt = ids;
			ids = idm;
			idm = i + 1;//m��id�����邽��i+1
		}
		else if (max > CRANEJointPos[i] && second <CRANEJointPos[i])
		{
			fourth = third;
			third = second;
			second = CRANEJointPos[i];
			idf = idt;
			idt = ids;
			ids = i + 1;
		}
		else if (max > CRANEJointPos[i] && second > CRANEJointPos[i] && third < CRANEJointPos[i])
		{
			fourth = third;
			third = CRANEJointPos[i];
			idf = idt;
			idt = i + 1;
		}
		else if (max > CRANEJointPos[i] && second > CRANEJointPos[i] && third > CRANEJointPos[i])
		{
			fourth = CRANEJointPos[i];
			idf = i + 1;
		}
	}

	crane.setCRANESpeeddata(idm, spdRatio_Middle);
	crane.setCRANESpeeddata(ids, spdRatio_Middle*(second / max));
	crane.setCRANESpeeddata(idt, spdRatio_Middle*(third / max));
	crane.setCRANESpeeddata(idf, spdRatio_Middle*(fourth / max));

	//�p�x�f�[�^�Z�b�g
	crane.setCRANEJointdata(targetJointPos);

	//Joint�\�t�g���~�b�g����
	Judge = crane.JointLimitJudgement();
	if (Judge != true){
		std::cout << "ERROR : Joint Soft Limit Over" << std::endl << std::endl;
		return RETURN_CODE(JARA_ARM::NG, "�I�y���[�V��������");
	}

	crane.ArmAction();

	std::cout << "Success" << std::endl << std::endl;

	return RETURN_CODE(JARA_ARM::OK, "�I�y���[�V�����𐳏�Ɏ󂯕t��");

}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::movePTPCartesianRel(const JARA_ARM::CarPosWithElbow& carPoint)
{
	std::cout << "movePTPCartesianRel" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::movePTPJointAbs(const JARA_ARM::JointPos& jointPoints)
{
	std::cout << "movePTPJointAbs" << std::endl;
	int i = 0, idm = 0, ids = 0, idt = 0, idf = 0;
	double setfabs = 0;
	int Judge;
	double CRANEJointPos[ARM_FREEDOM - 1];   //���̐�Βl
	double nowJointPos[ARM_FREEDOM - 1];     //���ݒl
	double targetJointPos[ARM_FREEDOM - 1];  //�ڕW�l
	double difference[ARM_FREEDOM - 1];      //���ݒl�ƖڕW�l�̍�
	double max = 0;      //���̏��ʕt��
	double second = 0;
	double third = 0;
	double fourth = 0;


	for (int i = 0; i<4; i++){
		std::cout << "JointPoint[" << i << "] = " << jointPoints[i] << std::endl;
	}

	targetJointPos[0] = jointPoints[0];
	targetJointPos[1] = jointPoints[1];
	targetJointPos[2] = jointPoints[2];
	targetJointPos[3] = jointPoints[3];

	crane.getCRANEJointdata(nowJointPos);

	//�ڕW�l�ƌ��ݒn�̍������
	for (int h = 0; h<ARM_FREEDOM - 1; h++){
		difference[h] = targetJointPos[h] - nowJointPos[h];
		setfabs = difference[h];
		CRANEJointPos[h] = fabs(setfabs);   //��Βl
	}


	//�ڕW�l�ƌ��ݒn�̍��ɂ���Ċ֐ߑ��x��ς���
	//�����傫���֐�id�����߂�
	max = CRANEJointPos[0];
	i = 0;
	idm = i + 1;
	for (i = 1; i<ARM_FREEDOM - 1; i++){
		if (max < CRANEJointPos[i]){
			fourth = third;
			third = second;
			second = max;
			max = CRANEJointPos[i];
			idf = idt;
			idt = ids;
			ids = idm;
			idm = i + 1;//m��id�����邽��i+1
		}
		else if (max > CRANEJointPos[i] && second <CRANEJointPos[i])
		{
			fourth = third;
			third = second;
			second = CRANEJointPos[i];
			idf = idt;
			idt = ids;
			ids = i + 1;
		}
		else if (max > CRANEJointPos[i] && second > CRANEJointPos[i] && third < CRANEJointPos[i])
		{
			fourth = third;
			third = CRANEJointPos[i];
			idf = idt;
			idt = i + 1;
		}
		else if (max > CRANEJointPos[i] && second > CRANEJointPos[i] && third > CRANEJointPos[i])
		{
			fourth = CRANEJointPos[i];
			idf = i + 1;
		}
	}

	crane.setCRANESpeeddata(idm, spdRatio_Middle);
	crane.setCRANESpeeddata(ids, spdRatio_Middle*(second / max));
	crane.setCRANESpeeddata(idt, spdRatio_Middle*(third / max));
	crane.setCRANESpeeddata(idf, spdRatio_Middle*(fourth / max));

	crane.setCRANEJointdata(targetJointPos);

	Judge = crane.JointLimitJudgement();
	if (Judge != true){
		std::cout << "ERROR : Joint Soft Limit Over" << std::endl << std::endl;
		return RETURN_CODE(JARA_ARM::NG, "�I�y���[�V��������");
	}

	crane.ArmAction();

	std::cout << "Success" << std::endl << std::endl;

	return RETURN_CODE(JARA_ARM::OK, "�I�y���[�V�����𐳏�Ɏ󂯕t��");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::movePTPJointRel(const JARA_ARM::JointPos& jointPoints)
{
	std::cout << "movePTPJointRel" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::openGripper()
{
	std::cout << "OpenGripper" << std::endl;
	crane.CRANEopenGripper();
	std::cout << "Success" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::OK, "�I�y���[�V�����𐳏�Ɏ󂯕t��");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::pause()
{
	std::cout << "pause" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::resume()
{
	std::cout << "resume" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::stop()
{
	std::cout << "stop" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setAccelTimeCartesian(::CORBA::Double aclTime)
{
	std::cout << "setAccelTimeCartesian" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setAccelTimeJoint(::CORBA::Double aclTime)
{
	std::cout << "setAccelTimeJoint" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setBaseOffset(const JARA_ARM::HgMatrix offset)
{
	std::cout << "setBaseOffset" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setControlPointOffset(const JARA_ARM::HgMatrix offset)
{
	std::cout << "setControlPointOffset" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setMaxSpeedCartesian(const JARA_ARM::CartesianSpeed& speed)
{
	std::cout << "setMaxSpeedCartesian" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");

}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setMaxSpeedJoint(const JARA_ARM::DoubleSeq& speed)
{
	std::cout << "setMaxSpeedJoint" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setMinAccelTimeCartesian(::CORBA::Double aclTime)
{
	std::cout << "setMinAccelTimeCartesian" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setMinAccelTimeJoint(::CORBA::Double aclTime)
{
	std::cout << "setMinAccelTimeJoint" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setSoftLimitCartesian(const JARA_ARM::LimitValue& xLimit, const JARA_ARM::LimitValue& yLimit, const JARA_ARM::LimitValue& zLimit)
{
	std::cout << "SetSoftLimitCartesian" << std::endl;
	Cartesian CartesianLimit;

	if ((xLimit.upper <= X_LimitMax) &&
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
		std::cout << "ERROR : Wrong Value" << std::endl << std::endl;
		return RETURN_CODE(JARA_ARM::VALUE_ERR, "�������s��");
	}

	std::cout << "Success" << std::endl << std::endl;

	return RETURN_CODE(JARA_ARM::OK, "�I�y���[�V�����𐳏�Ɏ󂯕t��");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setSpeedCartesian(JARA_ARM::ULONG spdRatio)
{
	std::cout << "setSpeedCartesian" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setSpeedJoint(JARA_ARM::ULONG spdRatio)
{
	std::cout << "SetSpeedJoint" << std::endl;
	std::cout << "setSpeed = " << spdRatio << "%" << std::endl;
	spdRatio_Middle = (double)spdRatio;

	if (spdRatio >= 1 && spdRatio <= 100){
		for (int i = 0; i<ARM_FREEDOM; i++){
			crane.setCRANESpeeddata(i, spdRatio_Middle);
		}
	}
	else{
		std::cout << "ERROR : Wrong Value" << std::endl << std::endl;
		return RETURN_CODE(JARA_ARM::VALUE_ERR, "�������s��");
	}

	std::cout << "Success" << std::endl << std::endl;

	return RETURN_CODE(JARA_ARM::OK, "�I�y���[�V�����𐳏�Ɏ󂯕t��");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::moveCircularCartesianAbs(const JARA_ARM::CarPosWithElbow& carPointR, const JARA_ARM::CarPosWithElbow& carPointT)
{
	std::cout << "moveCircularCartesianAbs" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::moveCircularCartesianRel(const JARA_ARM::CarPosWithElbow& carPointR, const JARA_ARM::CarPosWithElbow& carPointT)
{
	std::cout << "moveCircularCartesianRel" << std::endl;
	std::cout << "ERROR : �R�}���h������" << std::endl << std::endl;
	return RETURN_CODE(JARA_ARM::NOT_IMPLEMENTED, "�������̃R�}���h");
}


JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::setHome(const JARA_ARM::JointPos& jointPoint)
{

	std::cout << "SetHome" << std::endl;

	HomeMotorPosition[0] = (short)(jointPoint[0]);
	HomeMotorPosition[1] = (short)(jointPoint[1]);
	HomeMotorPosition[2] = (short)(jointPoint[2]);
	HomeMotorPosition[3] = (short)(jointPoint[3]);

	std::cout << "Success" << std::endl << std::endl;

	return RETURN_CODE(JARA_ARM::OK, "�I�y���[�V�����𐳏�Ɏ󂯕t��");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::getHome(JARA_ARM::JointPos_out jointPoint)
{
	std::cout << "GetHome" << std::endl;

	jointPoint = new JARA_ARM::JointPos;
	jointPoint->length(ARM_FREEDOM);

	(*jointPoint)[0] = HomeMotorPosition[0];
	(*jointPoint)[1] = HomeMotorPosition[1];
	(*jointPoint)[2] = HomeMotorPosition[2];
	(*jointPoint)[3] = HomeMotorPosition[3];

	std::cout << "Success" << std::endl << std::endl;

	return RETURN_CODE(JARA_ARM::OK, "�I�y���[�V�����𐳏�Ɏ󂯕t��");
}

JARA_ARM::RETURN_ID* JARA_ARM_ManipulatorCommonInterface_MiddleSVC_impl::goHome()
{
	int Judge;
	std::cout << "GoHome" << std::endl;
	crane.setCRANEJointdata(HomeMotorPosition);

	Judge = crane.JointLimitJudgement();
	if (Judge != true){
		std::cout << "ERROR : Joint Soft Limit Over" << std::endl << std::endl;
		return RETURN_CODE(JARA_ARM::NG, "�I�y���[�V��������");
	}

	crane.ArmAction();

	std::cout << "Success" << std::endl << std::endl;

	return RETURN_CODE(JARA_ARM::OK, "�I�y���[�V�����𐳏�Ɏ󂯕t��");
}




// End of example implementational code



