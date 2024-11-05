#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT_NUM) (REG=REG|(1<<BIT_NUM))
#define CLR_BIT(REG,BIT_NUM) (REG=REG&(~(1<<BIT_NUM)))
#define TOGGLE_BIT(REG,BIT_NUM) (REG=REG^(1<<BIT_NUM))
#define GET_BIT(REG,BIT_NUM) ((REG>>BIT_NUM)&0x01) 


#endif /* BIT_MATH_H_ */
