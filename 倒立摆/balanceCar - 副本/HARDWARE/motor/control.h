#ifndef   __CONTROL__H__
#define   __CONTROL__H__

#include "sys.h"

#define MAin1  PBout(5)
#define MAin2  PBout(4)    

#define MBin1  PBout(3)
#define MBin2  PAout(15)

void forword(void);

void Motor_Init(void);
void Load(int moto1);

#endif

