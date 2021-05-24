// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Projectile.h"
#include "Gametypes.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    // initialize the projectile movement
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
    ProjectileMovement->bAutoActivate = false;
    
    // initialize the collision mesh
    CollisionMesh   = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh Component"));
    SetRootComponent(CollisionMesh);
    CollisionMesh->SetNotifyRigidBodyCollision(true);
    CollisionMesh->SetVisibility(true);
    
    // initialize the launch blast
    LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast Component"));
    LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    
    // initialize the impact blast
    ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast Component"));
    ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    ImpactBlast->bAutoActivate = false;
    
    // initialize the explosion force
    ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
    ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    ExplosionForce->Radius = INIT_EXPLOSION_RADIUS;
    
    ProjectileDamage = INIT_PROJECTILE_DAMAGE;
}

void AProjectile::LaunchProjectile(float speed)
{
    if(ProjectileMovement)
    {
        ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
        ProjectileMovement->Activate();
    }
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
    CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                        UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
                        const FHitResult& Hit)
{
    LaunchBlast->Deactivate();
    ImpactBlast->Activate();
    
    // cause the force impulse
    ExplosionForce->FireImpulse();
    
    // reswitch root component to remove collision and the projectile's image
    SetRootComponent(ImpactBlast);
    CollisionMesh->DestroyComponent();
    
    // apply the damage
    UGameplayStatics::ApplyRadialDamage(this, ProjectileDamage, GetActorLocation(), ExplosionForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());
    
    // set a self-destroy timer on this projectile
    FTimerHandle timer;
    GetWorld()->GetTimerManager().SetTimer(timer, this, &AProjectile::OnTimerExpire, DestroyDelay, false);
}

void AProjectile::OnTimerExpire()
{
    Destroy();
}

