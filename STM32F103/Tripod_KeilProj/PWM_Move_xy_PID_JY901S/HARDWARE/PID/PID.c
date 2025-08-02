#include "PID.H"
#include <math.h>

pid_typedef pidx;
pid_typedef pidy;

float limit_output(float val, float max_val)
{
    if (val > max_val) return max_val;
    if (val < -max_val) return -max_val;
    return val;
}

void X_PID_init(float Kp,float Ki,float Kd)
{
	pidx.target_val=0;
	pidx.actual_val=0.0;
	pidx.err=0.0;
	pidx.err_last=0.0;
	pidx.out=0.0;
	pidx.err_sum=0.0;
	pidx.Kp=Kp;
	pidx.Ki=Ki;
	pidx.Kd=Kd;
}
void Y_PID_init(float Kp,float Ki,float Kd)
{
	pidy.target_val=0;
	pidy.actual_val=0.0;
	pidy.err=0.0;
	pidy.err_last=0.0;
	pidy.out=0.0;
	pidy.err_sum=0.0;
	pidy.Kp=Kp;
	pidy.Ki=Ki;
	pidy.Kd=Kd;
}

float PIDx_realize(float actual_val,float target_val)
{
	pidx.actual_val=actual_val;
	pidx.target_val=target_val;
  pidx.err=pidx.target_val-pidx.actual_val;
	
// 死区处理
  if (fabs(pidx.err) < 1.0f) return 0;
	
//  pidx.err_sum+=pidx.err;
//	pidx.err_sum = clamp(pidx.err_sum, -10, 10); // 限制积分
	// 积分分离：大误差时不积MAX_FREQ
    if (fabs(pidx.err) < 15.0f) {
        pidx.err_sum += pidx.err;
    } else {
        pidx.err_sum = 0;  // 避免大误差累积积分
    }

	// 限制积分范围
	pidx.err_sum = clamp(pidx.err_sum, -10, 10);
	
	pidx.out=pidx.Kp*pidx.err+pidx.Ki*pidx.err_sum+pidx.Kd*(pidx.err-pidx.err_last);
	pidx.err_last=pidx.err;
	
//// PID 输出进一步限制，靠近目标时软刹车
//if (fabs(pidx.err) < 15.0f)
//    pidx.out *= 0.4f;
		if (fabs(pidx.err) < 20.0f) {  
    float scale = fabs(pidx.err) / 20.0f;  // 误差越小，比例越小
    pidx.out *= scale;     // 最低20%，最高100%
}

		
	return limit_output(pidx.out, 10.0f); // 限制最大输出
 
//  return pidx.out;
}

float PIDy_realize(float actual_val,float target_val)
{
	pidy.actual_val=actual_val;
	pidy.target_val=target_val;
  pidy.err=pidy.target_val-pidy.actual_val;
	
	// 死区处理
  if (fabs(pidy.err) < 1.0f) return 0;
	

		// 积分分离：大误差时不积
    if (fabs(pidy.err) < 15.0f) {
        pidy.err_sum += pidy.err;
    } else {
        pidy.err_sum = 0;  // 避免大误差累积积分
    }
//	pidy.err_sum+=pidy.err;
//	pidy.err_sum = clamp(pidy.err_sum, -10, 10); // 限制积分
	
	pidy.out=pidy.Kp*pidy.err+pidy.Ki*pidy.err_sum+pidy.Kd*(pidy.err-pidy.err_last);
	pidy.err_last=pidy.err;
		
if (fabs(pidy.err) < 15.0f)
	pidy.out *= 0.4f;

	return limit_output(pidy.out,5.0f); // 限制最大输出
 
//  return pidy.out;
}