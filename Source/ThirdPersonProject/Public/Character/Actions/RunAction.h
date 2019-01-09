// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Actions/BaseAction.h"
#include "RunAction.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API URunAction : public UBaseAction
{
	GENERATED_BODY()
	
public:
    URunAction();

	virtual void Init() override;

	virtual void ActionTick(float DeltaTime) override;

	virtual bool Activate() override;

	virtual bool StopAction(bool bIsForce) override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Run)
	float StaminaPerSecond = 100.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Run)
	float StaminaToStartRun = 10.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Run)
	float RunSpeed = 700.0f;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Run)
    float AccelerationSpeed = 15.0f;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Run)
    float DecelerationSpeed = 30.0f;

private:	
	float DefaultWalkSpeed;
    float TargetSpeed;
    float InterpolationSpeed;
};
