#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	virtual void BeginPlay() override;

	void ApplyDamage(float Damage);
	bool IsDead() const;
	float GetCurrentHealth() const;

	UPROPERTY()
	FOnDeath OnDeath;
	UPROPERTY()
	FOnHealthChanged OnHealthChanged;

private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	float CurrentHealth = MaxHealth;
	bool bIsDead = false;

};
