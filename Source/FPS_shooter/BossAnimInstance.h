// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPS_SHOOTER_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	int32 mAttackIndex = 0;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>>	mAttackMontageArray;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>>	mDashMontageArray;

	void PlayAttackMontage();

	void PlayDashMontage();
	
};
