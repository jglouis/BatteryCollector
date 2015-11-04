// hexode.xyz

#include "BatteryCollector.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// All pickups start active
	bIsActive = true;

	// Create the static mesh component
	pickupMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));;
	RootComponent = pickupMesh;

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool APickup::IsActive()
{
	return bIsActive;
}

void APickup::SetActive(bool newPickupState)
{
	bIsActive = newPickupState;
}

