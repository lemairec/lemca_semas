#ifndef LEMCA_H_
#define LEMCA_H_

#ifdef __cplusplus
extern "C" {
#endif


extern void lemca_init();

void setAgressHyd(int agress_hydr);
int getAgressHyd();

extern void changeWorkState();
extern void setSpeedKmH(double kmh);
extern double getSpeedKmH();

extern void lemca_loop();


#ifdef __cplusplus
}
#endif

#endif