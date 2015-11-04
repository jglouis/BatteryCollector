// hexode.xyz

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Returns the pickup mesh */
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }

	/** Returns whether or not the pickup is active */
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive();

	/** change the activity state of the pickup */
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool newPickupState);

	/** Function to call when the pickup is collected */
	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();
	virtual void WasCollected_Implementation();

protected:
	/** true when the pickup can be used, false when deactivated */
	bool bIsActive;

private:
	// The static mesh representing the pickup
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh;
	
};
