// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "SimpleShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "BossAnimInstance.h"
#include "Engine/DamageEvents.h"

// Sets default values
ABossCharacter::ABossCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Attack"));

	AttackRadius = 50.0f;
	AttackRange = 200.0f;
}

// Called when the game starts or when spawned
void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
	mAnimInst = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
}

bool ABossCharacter::IsDead() const
{
	return Health <= 0;
}

float ABossCharacter::GetHealthPercentage() const
{
	return Health / MaxHealth;
}

// Called every frame
void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABossCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health Left %f"), Health);
	if (IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}
	return DamageToApply;
}

void ABossCharacter::Attack()
{
	mAnimInst->PlayAttackMontage();
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(50.0f),
		Params);

/*#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);

#endif
*/
	if (bResult) {
		FDamageEvent DamageEvent;//damage Event 엔진 헤더 전처리 하기 
		HitResult.GetActor()->TakeDamage(30.0f, DamageEvent, GetController(), this);
	}
}

void ABossCharacter::Dash()
{
	mAnimInst->PlayDashMontage();
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(50.0f),
		Params);
	if (bResult) {
		FDamageEvent DamageEvent;//damage Event 엔진 헤더 전처리 하기 
		HitResult.GetActor()->TakeDamage(60.0f, DamageEvent, GetController(), this);
	}
}

