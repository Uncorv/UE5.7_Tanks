#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ATankProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

	virtual void BeginPlay() override;

	void Fire(const FTransform &SpawnTransform);

private:
	void OnCooldownFinished();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATankProjectile> TankProjectile;

	UPROPERTY(EditAnywhere)
	float CooldownDuration = 2.f;

	FTimerHandle CooldownTimerHandle;
	bool bIsCooldownActive = false;
};
