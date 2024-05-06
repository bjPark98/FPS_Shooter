// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BT_ClearBlackBoard.generated.h"

/**
 * 
 */
UCLASS()
class FPS_SHOOTER_API UBT_ClearBlackBoard : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBT_ClearBlackBoard();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
