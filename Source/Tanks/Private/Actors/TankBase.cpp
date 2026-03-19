#include "Actors/TankBase.h"
#include "Components/BoxComponent.h"
#include "Components/HealthComponent.h"

ATankBase::ATankBase()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComponent->SetCollisionObjectType(ECC_Pawn);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Block);
	BoxComponent->SetNotifyRigidBodyCollision(true);

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	BaseMeshComponent->SetupAttachment(BoxComponent);
	BaseMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}

void ATankBase::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnDeath.AddDynamic(this, &ATankBase::OnDeath);
}

void ATankBase::OnDeath()
{
	Destroy();
	UE_LOG(LogTemp, Log, TEXT("ATankBase::OnDeath"));
}

ETeam ATankBase::GetTeam() const
{
	return Team;
}