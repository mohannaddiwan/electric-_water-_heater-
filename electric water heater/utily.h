


#ifndef UTILY_H_
#define UTILY_H_

#define setbit(reg,bit) reg|=(1<<bit)
#define clearbit(reg,bit) reg&=~(1<<bit)
#define toggelbit(reg,bit) reg^=(1<<bit)
#define readbit(reg,bit) ((reg>>bit)&1)
#define MAX_VALUE 75
#define MIN_VALUE 35
#endif 