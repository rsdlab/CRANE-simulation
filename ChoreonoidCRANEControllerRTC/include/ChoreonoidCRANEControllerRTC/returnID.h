//ReturnID.h
#ifndef __ReturnID_H__
#define __ReturnID_H__


static JARA_ARM::RETURN_ID* Set(int id, const char *comment)
{
  JARA_ARM::RETURN_ID_var RETURNCODE = new JARA_ARM::RETURN_ID;
  RETURNCODE->id = id;
  RETURNCODE->comment = comment;
  return RETURNCODE._retn(); 
}


#define SetCode(id,comment) { return Set(id,comment);}

#define RETURNID_OK SetCode(JARA_ARM::OK,"オペレーションを正常に受け付け.")
#define RETURNID_NG SetCode(JARA_ARM::NG,"オペレーション拒否.")
#define RETURNID_STATUS_ERR SetCode(JARA_ARM::STATUS_ERR,"オペレーションを受け付け可能な状態でない.")
#define RETURNID_VALUE_ERR SetCode(JARA_ARM::VALUE_ERR,"引数が不正.")
#define RETURNID_NOT_SV_ON_ERR SetCode(JARA_ARM::NOT_SV_ON_ERR,"全ての軸のサーボが入っていない.")
#define RETURNID_FULL_MOTION_QUEUE_ERR SetCode(JARA_ARM::FULL_MOTION_QUEUE_ERR,"バッファが一杯.")
#define RETURNID_NOT_IMPLEMENTED SetCode(JARA_ARM::NOT_IMPLEMENTED,"未実装のコマンド.")


#endif//__ReturnID_H__
