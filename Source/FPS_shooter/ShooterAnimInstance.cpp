// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "ShooterPlayerController.h"

void UShooterAnimInstance::PlayReloadMontage()
{
	if (!Montage_IsPlaying(mReloadMontageArray[mAttackIndex]))
	{
		Montage_SetPosition(mReloadMontageArray[mAttackIndex], 0.f);
		Montage_Play(mReloadMontageArray[mAttackIndex]);
		mAttackIndex = (mAttackIndex + 1) % mReloadMontageArray.Num(); 
	}
}

void UShooterAnimInstance::PlaySkillMontage()
{
	if (!Montage_IsPlaying(mSkillMontageArray[mAttackIndex]))
	{
		Montage_SetPosition(mSkillMontageArray[mAttackIndex], 0.f);
		Montage_Play(mSkillMontageArray[mAttackIndex]);
		mAttackIndex = (mAttackIndex + 1) % mSkillMontageArray.Num();
	}
}
