// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Launcher.generated.h"

/**
 * 
 */
UCLASS()
class FPS_SHOOTER_API ALauncher : public AGun
{
	GENERATED_BODY()

public:
	ALauncher();

	virtual void PullTrigger() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	USoundBase* LaunchSound;

};
