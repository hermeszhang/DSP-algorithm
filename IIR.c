/****************************************************************************/
/*                                                                          */
/*              无限长单位冲激响应滤波器测试                                */
/*                                                                          */
/*              2014年07月16日                                              */
/*                                                                          */
/****************************************************************************/
#include <stdio.h>                  // C 语言标准输入输出函数库
#include <math.h>                   // C 数学函数库

#include "mathlib.h"                // DSP 数学函数库
#include "dsplib.h"                 // DSP 函数库

#include <stdio.h>                 // C 语言标准输入输出函数库
#include <math.h>                  // C 语言数学函数库
#include <string.h>                // C 语言字符函数库

/****************************************************************************/
/*                                                                          */
/*              宏定义                                                      */
/*                                                                          */
/****************************************************************************/
// 软件断点
#define SW_BREAKPOINT     asm(" SWBP 0 ");

// 无限长单位冲激响应滤波器
// π 及 浮点数极小值
#define PI                3.14159
#define F_TOL             (1e-06)

/****************************************************************************/
/*                                                                          */
/*              全局变量                                                    */
/*                                                                          */
/****************************************************************************/
// 无限长单位冲激响应滤波器测试测试
// 测试无限长单位冲激响应滤波器
#define Tn  1024							// 样品数
#define Fs  1000.0							// 采样频率
#define N 	5								// 滤波器阶数

// 信号
// IIR 输入
#pragma DATA_ALIGN(IIR_In, 8);
float IIR_In[Tn];

// IIR 输出
#pragma DATA_ALIGN(IIR_Out, 8);
float IIR_Out[Tn+4];

// IIR延迟元素值
#pragma DATA_ALIGN(ptr_y1, 8);
float ptr_y1[Tn+4];

// IIR 系数
#pragma DATA_ALIGN (NUM, 8);
#pragma DATA_ALIGN (DEN, 8);
// 滑动平均系数
const int NL = 9;
const float NUM[9] = {0.0185630098,  0.07425203919,   0.1113780662,  0.07425203919,   0.0185630098};
// 自回归系数
const int DL = 9;
const float DEN[9] = {1,   -1.570398808,    1.275613308,  -0.4844033718,   0.07619706541};

/****************************************************************************/
/*                                                                          */
/*              函数声明                                                    */
/*                                                                          */
/****************************************************************************/
// 无限长单位冲激响应滤波器测试
void IIRTest();

/****************************************************************************/
/*                                                                          */
/*              主函数                                                      */
/*                                                                          */
/****************************************************************************/
int main(void)
{
	// IIR 测试
	IIRTest();

	// 断点
	SW_BREAKPOINT;
}

/****************************************************************************/
/*                                                                          */
/*              无限长单位冲激响应滤波器测试                                */
/*                                                                          */
/****************************************************************************/
// 无限长单位冲激响应滤波器
void IIRTest(void)
{
	//将延迟元素值全部清0
	memset(ptr_y1, 0, sizeof(ptr_y1));

	// 产生待测试信号 100hz信号 450hz噪声
	unsigned int i;
	for (i=0;i<Tn;i++)
		IIR_In[i]=5*sin(2*PI*100*(i/Fs))+15*sin(2*PI*450*(i/Fs));

	// IIR滤波
	DSPF_sp_iir (ptr_y1, IIR_In, IIR_Out, NUM, DEN, Tn+4);
}
