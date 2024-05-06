// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "SimpleShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterAnimInstance.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	mAnimInst = Cast<UShooterAnimInstance>(GetMesh()->GetAnimInstance());
	Health = MaxHealth;
	Gun = GetWorld()-> SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	//GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	//SkillShot->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Muzzle_03"));
	Gun->SetOwner(this);//멀티플레이어 & 데미지에 적용
	//SkillShot->SetOwner(this);
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

float AShooterCharacter::GetHealthPercentage() const
{
	return Health / MaxHealth;
}

float AShooterCharacter::GetMPPercentage() const
{
	return MP / MaxMP;
}
float AShooterCharacter::AmmoLeft() const
{
	return Ammo;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Reload);
	PlayerInputComponent->BindAction(TEXT("Swap"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Swap);
	PlayerInputComponent->BindAction(TEXT("Skill"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Skill);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent,EventInstigator,DamageCauser);
	DamageToApply = FMath::Min(Health,DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health Left %f"), Health);
	if (IsDead())
	{
		if (Gun != nullptr)
		{
			Gun->Destroy();
		}
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
		UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
		Destroy();
	}
	return DamageToApply;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}


void AShooterCharacter::Shoot()
{
	if (!bCanShoot)
	{
		return;
	}
	Gun->PullTrigger();
	Ammo--;
	if (Ammo <= 0)
	{
		bCanShoot = false;
	}
}

void AShooterCharacter::Reload()
{
	Ammo = 10;
	mAnimInst->PlayReloadMontage();
	bCanShoot = true;
}

void AShooterCharacter::Swap()
{
	if (Gun != nullptr)
	{
		Gun->Destroy();
		Gun = GetWorld()->SpawnActor<AGun>(GunArray[Index]);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		Gun->SetOwner(this);
		Index = (Index + 1) % GunArray.Num();
	}
}

void AShooterCharacter::Skill()
{
	if (MP == 0)
	{
		return;
	}
	mAnimInst->PlaySkillMontage();
	Gun -> SkillShot();
	MP -= 50;// 애니메이션 -> 데미지 -> 스킬 쿨 -> 마나감소 
}

