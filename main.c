
#include <assert.h>
#include <string.h>
#include "typedef.h"


individualElementStatus computeElementStatus(float monitoredElementValue, float elementMinRange, float elementMaxRange)
{
	individualElementStatus parameterStatus;
	parameterStatus.batteryIsOk = 1;

	if (monitoredElementValue < elementMinRange)
	{
		parameterStatus.individualStatus = belowRange;
		parameterStatus.batteryIsOk = 0;

	}
	else if (monitoredElementValue > elementMaxRange)
	{
		parameterStatus.individualStatus = aboveRange;
		parameterStatus.batteryIsOk = 0;
	}
	else
	{
		parameterStatus.individualStatus = inRange;
		
	}
	return parameterStatus;

}
compiledStatus computeBatteryState(float monitoredElementValue[noOfElements], float elementMinRange[noOfElements], float elementMaxRange[noOfElements]) {
	
	compiledStatus current_status;
	
	//Intialize overall status for every input 
	memset((void*)&current_status , 0, (sizeof(compiledStatus)));
	current_status.batteryIsOk = 1; // initialise battery status to ok once at the beginning 

	individualElementStatus parameterStatus;
	memset((void*)&parameterStatus, 0, (sizeof(individualElementStatus)));
	parameterStatus.batteryIsOk = 1;

	parameterStatus = computeElementStatus(monitoredElementValue[temp], elementMinRange[temp], elementMaxRange[temp]);
	current_status.elementStatus[temp] = parameterStatus.individualStatus;
	current_status.batteryIsOk &= parameterStatus.batteryIsOk;

	 parameterStatus = computeElementStatus(monitoredElementValue[soc], elementMinRange[soc], elementMaxRange[soc]);
	 current_status.elementStatus[soc] = parameterStatus.individualStatus;
	 current_status.batteryIsOk &= parameterStatus.batteryIsOk;

	 parameterStatus = computeElementStatus(monitoredElementValue[chargeRate], elementMinRange[chargeRate], elementMaxRange[chargeRate]);
         current_status.elementStatus[chargeRate] = parameterStatus.individualStatus;
     
	 current_status.batteryIsOk &= parameterStatus.batteryIsOk;
	

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
