// hexode.xyz

#include "BatteryCollector.h"
#include "BatteryPickup.h"

// Set default values
ABatteryPickup::ABatteryPickup(){
	GetMesh()->SetSimulatePhysics(true);
}

void ABatteryPickup::WasCollected_Implementation()
{
	// use base pickup behavior
	Super::WasCollected_Implementation();

	// Destroy the battery
	Destroy();
}


