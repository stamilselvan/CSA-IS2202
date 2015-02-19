#include <stdio.h>
#include <string.h>

main()
{

float l1,l2,l1_time,l2_time,l2_data,mem_time,tot;
l1 = 0.9950;
l2 = 0.9658;

l1_time = l1* 12;
//printf("\nL1:%f",l1_time);

l2_data = 1-l1;
//printf("\nL2_data:%f",l2_data);
l2_time = l2_data*l2* 12;
//printf("\nL2:%f",l2_time);

mem_time = (1-l1-(l2_data*l2))*200;

tot = l1_time + l2_time + mem_time;

printf("\n Total = %f", tot);
}
