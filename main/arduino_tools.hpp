#ifndef __TOOLS__H__
#define __TOOLS__H__


unsigned int waitFor(unsigned long *timer, unsigned long period){
	unsigned long newTime = micros() / period;              // numéro de la période modulo 2^32 
	int delta = newTime - *timer;              // delta entre la période courante et celle enregistrée
	if ( delta < 0 ) delta += 1 + (0xFFFFFFFF / period);    // en cas de dépassement du nombre de périodes possibles sur 2^32 
	if ( delta ) *timer = newTime;             // enregistrement du nouveau numéro de période
	return delta;
}

#endif