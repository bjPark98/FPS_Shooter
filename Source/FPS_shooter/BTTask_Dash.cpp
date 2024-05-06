// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Dash.h"
#include "BossCharacter.h"

UBTTask_Dash::UBTTask_Dash()
{
}

EBTNodeResult::Type UBTTask_Dash::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Boss = Cast<ABossCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (nullptr == Boss)
		return EBTNodeResult::Failed;

	Boss->Dash();
	return EBTNodeResult::Type();
}

void UBTTask_Dash::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecondes);
}
