// hexode.xyz

#include "BatteryCollector.h"
#include "BatteryPickup.h"

// Set default values
ABatteryPickup::ABatteryPickup(){
	GetMesh()->SetSimulatePhysics(true);

	// Set the defqult power of the bqttery
	BatteryPower = 250.0f;
}

void ABatteryPickup::WasCollected_Implementation()
{
	// use base pickup behavior
	Super::WasCollected_Implementation();

	// Destroy the battery
	Destroy();
}

float ABatteryPickup::GetPower()
{
	return BatteryPower;
}


