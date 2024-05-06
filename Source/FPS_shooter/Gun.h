// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class FPS_SHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	virtual void PullTrigger();

	void SkillShot();

	void FinishCoolDown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite)
	USceneComponent* ProjectileSpawnPoint;

	bool bIsCoolingDown = false;
	float CoolDownDuration = 2.8f;
	float CoolDownTimer = 0.0f;
	FTimerHandle SkillCoolTime;

private:
	UPROPERTY(VisibleAnywhere)//포인터는 편집 x 
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere)
	float MaxRange;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleHit;

	UPROPERTY(EditAnywhere)
	UParticleSystem* SkillHit;

	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	bool GunTrace(FHitResult &Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;

		
};
