#include "Components/TankMovementComponent.h"

UTankMovementComponent::UTankMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
}


void UTankMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTankMovementComponent::SetThrottle(float Value)
{
	if (!Owner)
	{
		return;
	}

	FVector Direction = Owner->GetActorForwardVector();
	FVector Delta = Direction * Value * MovementSpeed * GetWorld()->GetDeltaSeconds();

	Owner->AddActorWorldOffset(Delta, true);
}

void UTankMovementComponent::SetTurn(float Value)
{
	if (!Owner)
	{
		return;
	}

	FRotator DeltaRotation(0.f, Value * RotationSpeed * GetWorld()->GetDeltaSeconds(), 0.f);
	
	Owner->AddActorWorldRotation(DeltaRotation);
}
