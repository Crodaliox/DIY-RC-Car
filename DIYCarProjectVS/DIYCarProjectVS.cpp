#pragma comment(lib, "LogitechSteeringWheelLib.lib")
#include "LogitechSteeringWheelLib.h"
#include <iostream>
#include "ArduSerial.h"
#include "pch.h"


using namespace std;

DIJOYSTATE2ENGINES* state;

int rotVolantDeg;
float speedValue;
float brakeValue;
float clutchValue;

int speedValueNormal;
int brakeValueNormal;	

string dataaa = "hi";

void setup()
{
	Serial6.begin(115200);

	std::cout << "Starting..." << std::endl;

	while (!Serial6);

	while (Serial6.available())
		Serial6.read();

	std::cout << "Connected" << std::endl;
}

void loop()
{
	
}

int main()
{
	// Ouverture du port série
	setup();


	std::cout << "Hello World!\n";
	//the parameter determines whether you’ll use X-input or not
	LogiSteeringInitialize(TRUE);



	while (true)
	{
		if (LogiUpdate())
		{

			if (LogiIsConnected(0))
			{
				LogiPlaySpringForce(0, 0, 25, 25);

				//LogiPlayDirtRoadEffect(0, 20);


				state = LogiGetStateENGINES(0);
				rotVolantDeg = (float(state->lX) / 32767) * 450;
				speedValue = -(float(state->lY) / 65534) + 0.5;
				brakeValue = -(float(state->lRz) / 65534) + 0.5;
				clutchValue = -(float(state->rglSlider[0]) / 65534) + 0.5;

				speedValueNormal = speedValue * 255;
				brakeValueNormal = brakeValue * 255;

				cout << "Degree de volant : " << rotVolantDeg
					<< " | Accelerateur Normalisé: " << speedValueNormal
					<< " | Frein: " << brakeValueNormal
					<< " | embrayage:" << state->rglSlider[0]
					<< endl;
				
				Serial6.println(std::to_string(rotVolantDeg) + ";" + std::to_string(speedValueNormal));
				
				

			}
			else
			{
				cout << "volant pas connecté";
			}

			if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			{
				LogiStopSpringForce(0);
				LogiStopDirtRoadEffect(0);
				LogiStopSurfaceEffect(0);
				LogiSteeringShutdown();
			}
		}

	}

}