// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossCharacter.h"
#include "BossAIController.generated.h"


/**
 * 
 */
UCLASS()
class FPS_SHOOTER_API ABossAIController : public AAIController
{
	GENERATED_BODY()
public:
	ABossAIController();

	virtual void Tick(float DeltaSeconds) override;

	static const FName TargetKey;
	static const FName Distance;

	bool IsDead() const;

	UPROPERTY()
	float Radius;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BT_Boss;

	UPROPERTY(EditAnywhere)
	class UBlackboardData* BB_BossTree;
	
protected:
	virtual void BeginPlay() override;
};
