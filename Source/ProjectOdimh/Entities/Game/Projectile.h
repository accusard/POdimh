// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

// constants for initial values
const float INIT_PROJECTILE_DAMAGE = 1.0f;
const float INIT_EXPLOSION_RADIUS = 500.f;
const float INIT_LAUNCH_SPEED = 8000.0f;
const int32 INIT_AMMO_COUNT = 3;
const float INIT_TIME_BETWEEN_SHOTS = 0.1f;
const float INIT_AMMO_REPLENISH_TIME = 3.0f;
const float INIT_AMMO_TICK_TIME = 0.5f;

class UProjectileMovementComponent;
class URadialForceComponent;
class AProjectile;

USTRUCT()
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()
    
    /** The payload of the weapon system. */
    UPROPERTY(EditAnywhere)
    TSubclassOf<AProjectile> EquippedProjectileBP;
    
    /** The speed of this weapon system's projectile. */
    UPROPERTY(EditAnywhere)
    float LaunchSpeed;
    
    /**  */
    UPROPERTY()
    int32 CurrentAmmoCount;
    
    /** The max amount of ammo in reserve for this weapon system before it must reload. */
    UPROPERTY(EditAnywhere)
    int32 MaxAmmoCount;
    
    UPROPERTY(EditAnywhere)
    /** The amount of ammo that replenishes on a reload */
    int32 ReplenishAmount;
    
    /** The time in seconds for this weapon to be able to fire again. */
    UPROPERTY(EditAnywhere)
    double TimeBetweenShots;
    
    /** The time in seconds after the last time fired this weapon was fired before it starts its auto ammo replenishment. */
    UPROPERTY(EditAnywhere)
    float AmmoReplenishTime;
    
    /** The time in seconds between each ammo count replenishment. */
    UPROPERTY(EditAnywhere)
    float AmmoTickTime;
    
    /** The last time in seconds when this weapon system replenishes its ammo. */
    double LastTimeAmmoReplenished;
    
    /** The last time in seconds when a projectile was fired from this weapon. */
    double LastTimeWeaponFired;
    
    /** defaults */
    FWeaponData()
    {
        LaunchSpeed                 = INIT_LAUNCH_SPEED;
        MaxAmmoCount                = INIT_AMMO_COUNT;
        ReplenishAmount             = MaxAmmoCount;
        CurrentAmmoCount            = 0;
        TimeBetweenShots            = INIT_TIME_BETWEEN_SHOTS;
        AmmoReplenishTime           = INIT_AMMO_REPLENISH_TIME;
        AmmoTickTime                = INIT_AMMO_TICK_TIME;
        LastTimeAmmoReplenished     = 0;
        LastTimeWeaponFired         = 0;
    }
};

UCLASS()
class PROJECTODIMH_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

    void LaunchProjectile(float speed);
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    // delegate function to detect contact
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
               UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
               const FHitResult& Hit);
    
    // event
    UFUNCTION()
    void OnTimerExpire();
    
private:
    /** The movement behavior of this projectile */
    UPROPERTY(VisibleAnywhere)
    UProjectileMovementComponent* ProjectileMovement;
	
    /** A mesh to determine the collision bounds of this projectile */
    UPROPERTY(VisibleAnywhere, Category="Components")
    UStaticMeshComponent* CollisionMesh;
    
    /** The particle effect that occur during the spawning phase of this projectile */
    UPROPERTY(VisibleAnywhere, Category="Components")
    UParticleSystemComponent* LaunchBlast = nullptr;
    
    /** The particle effect that occur at the point of impact */
    UPROPERTY(VisibleAnywhere, Category="Components")
    UParticleSystemComponent* ImpactBlast = nullptr;
    
    /** The force of this explosion */
    UPROPERTY(VisibleAnywhere, Category="Components")
    URadialForceComponent* ExplosionForce = nullptr;
    
    // TODO: remove magic number
    /** The number of seconds before a projectile is given up for deletion after impact */
    UPROPERTY(EditDefaultsOnly, Category="Setup")
    float DestroyDelay = 10.0f;
    
    /** The amount of damage that this projectile does on impact */
    UPROPERTY(EditAnywhere, Category="Setup")
    float ProjectileDamage;
};
