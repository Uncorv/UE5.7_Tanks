#include "Components/WeaponComponent.h"
#include "Actors/TankProjectile.h"

UWeaponComponent::UWeaponComponent()
{

}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UWeaponComponent::Fire(const FTransform &SpawnTransform)
{
	if (bIsCooldownActive)
		return;


	UWorld* World = GetWorld();
	if (World)
	{
		FVector SpawnLocation = SpawnTransform.GetLocation();
		FRotator SpawnRotation = SpawnTransform.Rotator();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();

		ATankProjectile *Projectile = World->SpawnActor<ATankProjectile>(
			TankProjectile,
			SpawnLocation,
			SpawnRotation,
			SpawnParams
		);

		bIsCooldownActive = true;
		GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UWeaponComponent::OnCooldownFinished, CooldownDuration, false);
	}
}

void UWeaponComponent::OnCooldownFinished()
{
	bIsCooldownActive = false;
}

bool UWeaponComponent::CanFire() const
{
	if (bIsCooldownActive)
		return false;
	else
		return true;
}