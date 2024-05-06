// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossAttack.h"
#include "BossCharacter.h"
#include "AIController.h"
#include "BossAnimInstance.h"

UBTTask_BossAttack::UBTTask_BossAttack()
{
	NodeName = TEXT("Boss_Attack");
}

EBTNodeResult::Type UBTTask_BossAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//nullptr값인지 언제나 먼저 체크
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ABossCharacter* Character = Cast<ABossCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	Character->Attack();
	return EBTNodeResult::Succeeded;//다음 지시를 내리기전까지 끝?
}
