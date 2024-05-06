// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyService_PlayerLocationIfSeen.generated.h"

/**
 * 
 */
UCLASS()
class FPS_SHOOTER_API UMyService_PlayerLocationIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UMyService_PlayerLocationIfSeen();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
