#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void setup_gpio();

void readAll2(int * capteur_angle, int * capteur_h, int * machine_l, int * machine_r);
void setElectrovanne(int left, int right, int up, int down);

#ifdef __cplusplus
}
#endif

#endif