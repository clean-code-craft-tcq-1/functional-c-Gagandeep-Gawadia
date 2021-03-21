
#include <assert.h>
#include <string.h>
#include "typedef.h"

compiledStatus computeBatteryState(float monitoredElementValue[noOfElements], float elementMinRange[noOfElements], float elementMaxRange[noOfElements]) {
	
	compiledStatus current_status;
	
	//Intialize overall status for every input, the status is inRange by default
	memset((void*)&current_status , 0, (sizeof(compiledStatus)));
	current_status.batteryIsOk = true;

	for (int elementNo = 0; elementNo < noOfElements; elementNo++)
	{
		if (monitoredElementValue[elementNo] < elementMinRange[elementNo])
		{
			current_status.elementStatus[elementNo] = belowRange;
			current_status.batteryIsOk = false;

		}
		else if (monitoredElementValue[elementNo] > elementMaxRange[elementNo])
		{
			current_status.elementStatus[elementNo] = aboveRange;
			current_status.batteryIsOk = false;
		}
		//else
		//{
		//	current_status.elementStatus[elementNo] = inRange;
			//current_status.batteryIsOk = true; // do not overwrite true at anytime once the bit is set to false
		//}
	}

	return current_status;
}

int main() {

	float monitoredElementValue[noOfElements] = {0};
	float elementMinRange[noOfElements] = { TempMin,socMin ,chargeRateMin };
	float elementMaxRange[noOfElements] = { TempMax,socMax ,chargeRateMax };
	
	compiledStatus battery_status;

	//Temperature is above range
	monitoredElementValue[temp] = 46.f;
	monitoredElementValue[soc] = 60.f;
	monitoredElementValue[chargeRate] = 0.7f;

	//Calling test function
	battery_status = computeBatteryState(monitoredElementValue, elementMinRange, elementMaxRange);

	//Expected result
	assert(!battery_status.batteryIsOk);

	//Temperature is below range
	monitoredElementValue[temp] = -1.f;
	monitoredElementValue[soc] = 60.f;
	monitoredElementValue[chargeRate] = 0.7f;
	
	//Calling test function
	battery_status = computeBatteryState(monitoredElementValue, elementMinRange, elementMaxRange);

	//Expected result
	assert(!battery_status.batteryIsOk);

	//soc is above range
	monitoredElementValue[temp] = 35;
	monitoredElementValue[soc] = 85;
	monitoredElementValue[chargeRate] = 0.7f;
	
	//Calling test function
	battery_status = computeBatteryState(monitoredElementValue, elementMinRange, elementMaxRange);

	//Expected result
	assert(!battery_status.batteryIsOk);
	
	//soc is below range
	monitoredElementValue[temp] = 35;
	monitoredElementValue[soc] = 15;
	monitoredElementValue[chargeRate] = 0.7f;
	
	//Calling test function
	battery_status = computeBatteryState(monitoredElementValue, elementMinRange, elementMaxRange);

	//Expected result
	assert(!battery_status.batteryIsOk);
	
	// charge rate is above range
	monitoredElementValue[temp] = 35;
	monitoredElementValue[soc] = 50;
	monitoredElementValue[chargeRate] = 0.9f;
	
	//Calling test function
	battery_status = computeBatteryState(monitoredElementValue, elementMinRange, elementMaxRange);

	//Expected result
	assert(!battery_status.batteryIsOk);
	
	//Boundary condition for charge rate element still inRange
	monitoredElementValue[temp] = 35;
	monitoredElementValue[soc] = 50;
	monitoredElementValue[chargeRate] = 0.f;
	
	//Calling test function
	battery_status = computeBatteryState(monitoredElementValue, elementMinRange, elementMaxRange);

	//Expected result
	assert(battery_status.batteryIsOk);
	
	//Battery is running normal, all elements are inRange
	monitoredElementValue[temp] = 35;
	monitoredElementValue[soc] = 50;
	monitoredElementValue[chargeRate] = 0.2f;
	
	//Calling test function
	battery_status = computeBatteryState(monitoredElementValue, elementMinRange, elementMaxRange);

	//Expected result
	assert(battery_status.batteryIsOk);

}

