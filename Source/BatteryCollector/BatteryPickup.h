// hexode.xyz

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABatteryPickup();
	
	/** Override WasCollected function - use Implementation because it a blueprint native event */
	void WasCollected_Implementation() override;
	
};
