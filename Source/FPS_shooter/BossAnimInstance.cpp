// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAnimInstance.h"
#include "BossCharacter.h"


void UBossAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(mAttackMontageArray[mAttackIndex]))
	{
		Montage_SetPosition(mAttackMontageArray[mAttackIndex], 0.f);
		Montage_Play(mAttackMontageArray[mAttackIndex]);
		mAttackIndex = /*(mAttackIndex + 1)*/rand() % mAttackMontageArray.Num();
	}
}

void UBossAnimInstance::PlayDashMontage()
{
	if (!Montage_IsPlaying(mDashMontageArray[mAttackIndex]))
	{
		Montage_SetPosition(mDashMontageArray[mAttackIndex], 0.f);
		Montage_Play(mDashMontageArray[mAttackIndex]);
		mAttackIndex = rand() % mDashMontageArray.Num();
	}
}
