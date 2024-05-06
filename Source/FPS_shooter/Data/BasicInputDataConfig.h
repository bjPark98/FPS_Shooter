// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "BasicInputDataConfig.generated.h"

/**
 * 
 */
UCLASS()
class FPS_SHOOTER_API UBasicInputDataConfig : public UInputAction
{
	GENERATED_BODY()

public:
	UInputMappingContext* DefaultContext = nullptr;

public:
	UInputAction* IA_MoveForward = nullptr;
	UInputAction* IA_LookUp = nullptr;
};
