#include "Pawns/TankPawn.h"
#include "GameModes/TanksGameMode.h"
#include "Actors/TankProjectile.h"
#include "Components/BoxComponent.h"
#include "Components/TankMovementComponent.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Box->SetCollisionObjectType(ECC_Pawn);
	Box->SetCollisionResponseToAllChannels(ECR_Block);
	Box->SetNotifyRigidBodyCollision(true);

	HullMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HullMesh"));
	HullMesh->SetupAttachment(Box);
	HullMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(HullMesh);
	TurretMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MuzzlePoint = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzlePoint"));
	MuzzlePoint->SetupAttachment(TurretMesh);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(TurretMesh);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	MovementComponent = CreateDefaultSubobject<UTankMovementComponent>(TEXT("MovementComponent"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));

}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
	HealthComponent->OnDeath.AddDynamic(this, &ATankPawn::OnTankDeath);

}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATankPawn::MoveForward(float Value)
{
	MovementComponent->SetThrottle(Value);
}

void ATankPawn::TurnRight(float Value)
{
	MovementComponent->SetTurn(Value);
}

void ATankPawn::Fire()
{
	WeaponComponent->Fire(MuzzlePoint->GetComponentTransform());
}

bool ATankPawn::CanFire() const
{
	return WeaponComponent->CanFire();
}

float ATankPawn::GetCurrentHealth() const
{
	return HealthComponent->GetCurrentHealth();
}

void ATankPawn::TurnCameraAndTurret(float Value)
{
	AddControllerYawInput(Value);

	if (TurretMesh)
	{
		FRotator CurrentRotation = TurretMesh->GetRelativeRotation();
		CurrentRotation.Yaw += Value * TurretRotationSpeed * GetWorld()->GetDeltaSeconds();
		TurretMesh->SetRelativeRotation(CurrentRotation);
	}
}

FRotator ATankPawn::GetCurrentTurretRotation() const
{
	return TurretMesh->GetComponentRotation();
}

FVector ATankPawn::GetCurrentTurretLocation() const
{
	return TurretMesh->GetComponentLocation();
}

void ATankPawn::OnTankDeath()
{
	//TODO Destroy
	UE_LOG(LogTemp, Log, TEXT("ATankPawn::OnTankDeath"));
	Destroy();

	AGameModeBase *BGM = GetWorld()->GetAuthGameMode();
	ATanksGameMode *TGM = Cast<ATanksGameMode>(BGM);
	if (TGM)
	{
		TGM->HandleTankDestroyed(Team);
	}
}

ETeam ATankPawn::GetTeam() const
{
	return Team;
}

bool ATankPawn::IsDead() const
{
	return HealthComponent->IsDead();
}