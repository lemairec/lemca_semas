#ifndef LEMCA_H_
#define LEMCA_H_

#ifdef __cplusplus
extern "C" {
#endif


extern void lemca_init();

void setAgressHyd(int agress_hydr);
int getAgressHyd();

extern void changeWorkState();
extern int getWorkState();
extern void setSpeedKmH(double kmh);
extern double getSpeedKmH();

extern void lemca_loop();

extern void onButtonUp();
extern void onButtonDown();
extern void onButtonUpLeft();
extern void onButtonUpRight();

extern void onButtonUpWork();
extern void onButtonDownWork();
void setWorkHeight(int work_height);
int getWorkHeight();

extern int getLastRight();
extern int getLastLeft();

#ifdef __cplusplus
}
#endif

#endif