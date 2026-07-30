#pragma comment(lib, "LogitechSteeringWheelLib.lib")
#include "LogitechSteeringWheelLib.h"
#include <iostream>
#include "ArduSerial.h"
#include "pch.h"
#include <chrono>


using namespace std;

DIJOYSTATE2* state;

int rotVolantDeg;
float speedValue;
float brakeValue;
float clutchValue;

int speedValueNormal;
int brakeValueNormal;	

static bool initialized = false;

auto lastSend = std::chrono::steady_clock::now();
auto now = std::chrono::steady_clock::now();

string dataaa = "hi";

void setup()
{
	Serial4.begin(115200);

	std::cout << "Starting..." << std::endl;

	while (!Serial4);

	while (Serial4.available())
		Serial4.read();

	std::cout << "Connected" << std::endl;
}

void loop()
{
	
}

int main()
{
	// Ouverture du port série
	setup();




	//the parameter determines whether you’ll use X-input or not
	LogiSteeringInitialize(FALSE);
	

	



	while (true)
	{
		if (LogiUpdate())
		{
			



			if (LogiIsConnected(0))
			{
				LogiPlaySpringForce(0, 0, 25, 25);

				//LogiPlayDirtRoadEffect(0, 20);


				state = LogiGetState(0);

				if (state == nullptr)
				{
					cout << "Erreur: Impossible de récupérer l'état du volant. (state null)" << endl;
					continue;
					
				}

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
				


				if (!initialized)
				{
					if (speedValueNormal < 5)   // Au début, lY est à 127, Dès que l'utilisateur touche et relache la pédale, c'est good. donc on attend que la pédale soit bougé et relacher pour initialiser les valeurs
						initialized = true;
					else
						continue;
				}

				now = std::chrono::steady_clock::now();

				// Envoi toutes les 100 ms = 10 Hz
				if (now - lastSend >= std::chrono::milliseconds(100))
				{
					Serial4.println(
						std::to_string(rotVolantDeg) + ";" +
						std::to_string(speedValueNormal)
					);
					lastSend = now;
				}

				

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