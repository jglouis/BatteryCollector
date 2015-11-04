// hexode.xyz

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** Returns WhereToSpawn subobject */
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; };

	/** Finds a random point within the box component */
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();

private:
	/** Box component to specify wherepickups should be spawned */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WhereToSpawn;
	
};
