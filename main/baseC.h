#ifndef DEF_BASEC
#define DEF_BASEC

#include "esp32.h"

class baseC : public esp32
{
private:
	bool setFlex

public :
	void readFlex(const int Pin, const float R_DIV, const float straightR, const float bendR);
	void readTilt(const int Pin); //Inclinaison
	void readAccGyro();
	void setupFlex(bool setFlex);

}

#endif