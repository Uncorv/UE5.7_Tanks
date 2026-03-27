#include "Components/HealthComponent.h"

UHealthComponent::UHealthComponent()
{

}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UHealthComponent::ApplyDamage(float Damage)
{
	if (bIsDead)
		return;
	
	CurrentHealth -= Damage;
	OnHealthChanged.Broadcast();

	UE_LOG(LogTemp, Log, TEXT("UHealthComponent::ApplyDamage, Health = %f"), CurrentHealth);

	if (CurrentHealth <= 0.f)
	{
		bIsDead = true;
		OnDeath.Broadcast();
	}
}

bool UHealthComponent::IsDead() const
{
	return bIsDead;
}

float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}