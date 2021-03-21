
#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define TempMax  45.f
#define TempMin  0.f

#define socMax 80.f
#define socMin 20.f

#define chargeRateMax  0.8f
#define chargeRateMin  0.f

#define noOfElements 3

#define temp 0
#define soc 1
#define chargeRate 2

typedef enum status {
	inRange,
	belowRange,
	aboveRange,
} status;

typedef struct compiledstatus
{
	status elementStatus[noOfElements];
	int    batteryIsOk : 1;
 }compiledStatus;

typedef struct individualElementStatus
{
	status individualStatus;
	int    batteryIsOk : 1 ;
}individualElementStatus;

#endif
