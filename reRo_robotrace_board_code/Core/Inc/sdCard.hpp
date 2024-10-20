/*
 * sdCard.hpp
 *
 *  Created on: Jun 22, 2023
 *      Author: SHIMOTORI Haruki
 */

#ifndef INC_SDCARD_HPP_
#define INC_SDCARD_HPP_

#include "fatfs.h"

#define BUFF_SIZE 128

class sdCard{
private:
	FATFS fs_;
	FIL fil_;
	FRESULT fresult;
	char buffer_[BUFF_SIZE];
	UINT br_, bw_;

	FATFS *pfs;
	DWORD fre_clust;
	uint32_t total, free_space;

	char filepath_[64];
	char dirpath_[64];

	void openFile(const char *, const char *);
	void clearBuff();

public:
	sdCard();

	bool init();
	bool mount();
	bool unmout();
	void userFopen(const char *, const char *);
	void userFclose();
	void write(const char *, const char * , uint16_t, float *);
	void read(const char *, const char * , uint16_t, float *);
};



#endif /* INC_SDCARD_HPP_ */
