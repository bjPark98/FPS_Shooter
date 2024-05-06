// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterAIController.h"

const FName ABossAIController::Distance(TEXT("Distance"));
const FName ABossAIController::TargetKey(TEXT("TargetKey"));

ABossAIController::ABossAIController()
{
}

void ABossAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool ABossAIController::IsDead() const
{
	ABossCharacter* ControlledCharacter = Cast<ABossCharacter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}
	return true;
}

void ABossAIController::BeginPlay()
{
	Super::BeginPlay();
	if (BT_Boss != nullptr)
	{
		RunBehaviorTree(BT_Boss);
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

