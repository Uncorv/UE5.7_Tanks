// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UTankMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankMovementComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetThrottle(float Value);
	void SetTurn(float Value);

private:
	UPROPERTY()
	AActor *Owner = nullptr;
	UPROPERTY(EditAnywhere)
	float MovementSpeed = 600.f;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 200.f;
};
