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
	
// ��������
  if (fabs(pidx.err) < 1.0f) return 0;
	
//  pidx.err_sum+=pidx.err;
//	pidx.err_sum = clamp(pidx.err_sum, -10, 10); // ���ƻ���
	// ���ַ��룺�����ʱ����MAX_FREQ
    if (fabs(pidx.err) < 15.0f) {
        pidx.err_sum += pidx.err;
    } else {
        pidx.err_sum = 0;  // ���������ۻ�����
    }

	// ���ƻ��ַ�Χ
	pidx.err_sum = clamp(pidx.err_sum, -10, 10);
	
	pidx.out=pidx.Kp*pidx.err+pidx.Ki*pidx.err_sum+pidx.Kd*(pidx.err-pidx.err_last);
	pidx.err_last=pidx.err;
	
//// PID �����һ�����ƣ�����Ŀ��ʱ��ɲ��
//if (fabs(pidx.err) < 15.0f)
//    pidx.out *= 0.4f;
		if (fabs(pidx.err) < 20.0f) {  
    float scale = fabs(pidx.err) / 20.0f;  // ���ԽС������ԽС
    pidx.out *= scale;     // ���20%�����100%
}

		
	return limit_output(pidx.out, 10.0f); // ����������
 
//  return pidx.out;
}

float PIDy_realize(float actual_val,float target_val)
{
	pidy.actual_val=actual_val;
	pidy.target_val=target_val;
  pidy.err=pidy.target_val-pidy.actual_val;
	
	// ��������
  if (fabs(pidy.err) < 1.0f) return 0;
	

		// ���ַ��룺�����ʱ����
    if (fabs(pidy.err) < 15.0f) {
        pidy.err_sum += pidy.err;
    } else {
        pidy.err_sum = 0;  // ���������ۻ�����
    }
//	pidy.err_sum+=pidy.err;
//	pidy.err_sum = clamp(pidy.err_sum, -10, 10); // ���ƻ���
	
	pidy.out=pidy.Kp*pidy.err+pidy.Ki*pidy.err_sum+pidy.Kd*(pidy.err-pidy.err_last);
	pidy.err_last=pidy.err;
		
if (fabs(pidy.err) < 15.0f)
	pidy.out *= 0.4f;

	return limit_output(pidy.out,5.0f); // ����������
 
//  return pidy.out;
}