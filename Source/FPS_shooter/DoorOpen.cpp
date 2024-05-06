// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpen.h"
#include "Components/BoxComponent.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"

// Sets default values
ADoorOpen::ADoorOpen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetBoxExtent(FVector(40.f, 40.f, 40.f));
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = Trigger;

	LevelSequence = CreateDefaultSubobject<ULevelSequence>(TEXT("LevelSequence"));
	LevelSequenceActor = CreateDefaultSubobject<ALevelSequenceActor>(TEXT("LevelSequenceActor"));
	
	 

}

// Called when the game starts or when spawned
void ADoorOpen::BeginPlay()
{
	Super::BeginPlay();

	FMovieSceneSequencePlaybackSettings Settings;
	Settings.bAutoPlay = false;
	Settings.bPauseAtEnd = true;
	LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, Settings, LevelSequenceActor);
	
}

// Called every frame
void ADoorOpen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorOpen::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (LevelSequencePlayer)
	{
		LevelSequencePlayer->Play();
	}
}

void ADoorOpen::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (LevelSequencePlayer)
	{
		LevelSequencePlayer->PlayReverse();
	}
}



