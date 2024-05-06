// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameModeBase.h"
#include "EngineUtils.h"
#include "GameFrameWork/Controller.h"
#include "ShooterAIController.h"
#include "BossAIController.h"

void AKillEmAllGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!Controller->IsDead())
		{
			return;
		}//이중문 쓰면 될거같긴한데 .. 
	}

	for (ABossAIController* Controller : TActorRange<ABossAIController>(GetWorld()))
	{
		if (!Controller->IsDead())
		{
			return;
		}//이중문 쓰면 될거같긴한데 .. 
	}
	EndGame(true);
	//For Loop ShooterAI In World;
	//Is not Dead?
	 //return
	  
	 //end Game    
}

void AKillEmAllGameModeBase::EndGame(bool bIsPlayerWinner)
{
	//월드에 모든 controller에 변수로 저장된다 라는 뜻 
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
		}
	}
