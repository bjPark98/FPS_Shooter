// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShooterAnimInstance.generated.h"


UENUM(BluePrintType)
enum class EPlayerAnimType : uint8
{
	Base,//idle & jump & Death 3개다 포함
	Shot,//rifle by Animation Montage 
};
UCLASS()
class FPS_SHOOTER_API UShooterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	int32 mAttackIndex = 0;
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPlayerAnimType	mAnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>>	mReloadMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>>	mSkillMontageArray;

public:
	void SetAnimType(EPlayerAnimType Type)
	{
		mAnimType = Type;
	}

	void PlayReloadMontage();

	void PlaySkillMontage();
};
