#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/Team.h"
#include "TankBase.generated.h"

class UBoxComponent;
class UHealthComponent;

UCLASS()
class TANKS_API ATankBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATankBase();

	void BeginPlay() override;

	UFUNCTION()
	void OnBaseDeath();

	ETeam GetTeam() const;
	bool IsDead() const;

private:
	UPROPERTY(EditAnywhere)
	UBoxComponent *BoxComponent;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *BaseMeshComponent;
	UPROPERTY(EditAnywhere)
	UHealthComponent *HealthComponent;
	UPROPERTY(EditAnywhere)
	ETeam Team = ETeam::None;
	bool bIsDead = false;

};
