#ifndef LEMCA_H_
#define LEMCA_H_

#ifdef __cplusplus
extern "C" {
#endif

int isAlive();
void decreaseAlive();

void setSpeedKmH(double speed_kmh);
double getSpeedKmH();

int getWorkState();
void changeWorkState();

void setRearWork(int inwork);
int getRearWork();

int getSection(int i);
int getTCSection();
void setTCSection(int value);

void startManualSectionLeft();
void startManualSectionRight();


void send_message_aux(int touch);

void lemca_loop();

#ifdef __cplusplus
}
#endif

#endif