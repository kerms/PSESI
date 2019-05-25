/*****************************************************************
FIFO used to store and transmit data
*****************************************************************/

#ifndef __FIFO_H__
#define __FIFO_H__

class Fifo
{
private:
	float*	buffer;
	int 	PTW;		//Write "pointer"
	int 	PTR;		//Read  "pointer"
	int		status;
	int		size;

public:
	Fifo(int size=250) : size(size)
	{
		buffer 	= new float[250];
		PTW 	= 0;
		PTR 	= 0;
		status 	= 0;
	}

	float* getBuf(){
		return buffer;
	}

	int getPTW(){
		return PTW;
	}

	int getPTR(){
		return PTR;
	}

	int getStatus(){
		return status;
	}

	int getSize(){
		return size;
	}

	// Write into the buffer data and return 1 in case of success or 0 if full ( status = size )
	bool writeBuf(float data){
		if(status<size){
			if(PTW < size){
				buffer[PTW]	= data;
				PTW++;
				status++;
				return 1;
			}
			else{
				PTW = 0;
				buffer[PTW]	= data;
				PTW++;
				status++;
				return 1;
			}
		return 0;
		}
	}

	// Check if we can read into the buffer data for size amount of data. Return 1 in case of success or 0
	bool canRead(int size){
		if(status >= size){
			return 1;
		}
		return 0;
	}

	// Set the PTR at a certain value corresponding to the amount of data we want to read
	void setPTR(int i){
		if(status >= i){
			PTR 	= (PTR + i)%size;
			status -= i;
		}
	}

	// Read one data from buffer
	bool readBufr(float* data){
		float val;
		if(status > 0){
			if(PTR < size){
				val = buffer[PTR];
				PTR++;
				status--;
				data *= val;
				return 1;
			}

			else{
				PTR = 0:
				val = buffer[PTR];
				PTR++;
				status--;
				data *= val;
				return 1;
			}
		}
		return 0;
	}


}



#endif