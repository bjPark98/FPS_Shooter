// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossAnimInstance.h"
#include "BossCharacter.generated.h"

UCLASS()
class FPS_SHOOTER_API ABossCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;//죽은순간 바뀌면안됨 

	UFUNCTION(BlueprintPure)
	float GetHealthPercentage() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
	//데미지는 피해를 입은 액터에 관련 로직을 설정해 주어야 한다
	void Attack();

	void Dash();

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 300;

	class UBossAnimInstance* mAnimInst;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRadius;


private:
	UPROPERTY(VisibleAnywhere)
	float Health = 300;

};
