// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_ClearBlackBoard.h"
#include "BehaviorTree/BlackboardComponent.h"
UBT_ClearBlackBoard::UBT_ClearBlackBoard()
{
	NodeName = TEXT("Clear BlackBoard Value");
}

EBTNodeResult::Type UBT_ClearBlackBoard::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;//다음 지시를 내리기전까지 끝?
}
