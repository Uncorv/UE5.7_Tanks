#include "Actors/TankProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/HealthComponent.h"

ATankProjectile::ATankProjectile()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Block);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshCpmponent"));
	ProjectileMesh->SetupAttachment(SphereComponent);
	ProjectileMesh->SetSimulatePhysics(false);

	//TODO Make BP class
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Meshes/ProjectileMesh"));
	ProjectileMesh->SetStaticMesh(Mesh.Object);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	ProjectileMovementComponent->SetUpdatedComponent(SphereComponent);
	ProjectileMovementComponent->InitialSpeed = ProjSpeed;
	ProjectileMovementComponent->MaxSpeed = ProjSpeed;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->OnComponentHit.AddDynamic(this, &ATankProjectile::OnHit);
	SphereComponent->IgnoreActorWhenMoving(GetOwner(), true);
}

void ATankProjectile::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	if (!OtherActor || OtherActor == GetOwner())
		return;
	UHealthComponent *HealthComp = OtherActor->FindComponentByClass<UHealthComponent>();
	if (HealthComp)
	{
		HealthComp->ApplyDamage(Damage);
	}
	Destroy();
}
