// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"


class AGun; //포워드 선언은 컴파일링 시간을많이줄여줌 근데 이게 왜 오류를 해결해주징 ?

UCLASS()
class FPS_SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintPure)
	bool IsDead() const;//죽은순간 바뀌면안됨 
	// Called every frame

	UFUNCTION(BlueprintPure)
	float GetHealthPercentage() const;

	UFUNCTION(BlueprintPure)
	float GetMPPercentage() const;

	UFUNCTION(BlueprintPure)
	float AmmoLeft() const;

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

	void Shoot();

	void Reload();

	void Swap();

	void Skill();

	class UShooterAnimInstance* mAnimInst;

	UPROPERTY(BlueprintReadWrite)
	float MaxHealth = 100;

	UPROPERTY(BlueprintReadWrite)
	float MaxMP = 100;


	UPROPERTY(BlueprintReadWrite)
	float Health = 100;

	UPROPERTY(BlueprintReadWrite)
	float MP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AGun>> GunArray;


	//여기서 Binding 해야함 
private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	//void LookUp(float AxisValue);
	//void LookRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	

	UPROPERTY(EditAnywhere)
	float RotationRate = 5; //상하좌우에 동일한 속도

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;


	UPROPERTY(EditAnyWhere)
	float Ammo = 10;

	bool bCanShoot = true;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere)
	class USoundBase* DeathSound;

	UPROPERTY()
	AGun* Gun; //클래스 인스턴스 생성하면 여기에 저장


	int32 Index = 0;

};
