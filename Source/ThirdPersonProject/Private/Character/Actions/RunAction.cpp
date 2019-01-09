// Fill out your copyright notice in the Description page of Project Settings.

#include "RunAction.h"
#include "BaseCharacter.h"
#include "CharacterActionsComponent.h"
#include "CharacterStatsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

URunAction::URunAction()
{
    bTickOnlyIfActive = false;
    Type = EActionType::Run;
}

void URunAction::Init()
{
	Super::Init();

	if (IsValid(OwnerCharacter))
	{
        TargetSpeed = DefaultWalkSpeed = OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed;
	}
}

void URunAction::ActionTick(float DeltaTime)
{
	Super::ActionTick(DeltaTime);

	if (!IsValid(OwnerCharacter))
	{
		return;
	}

    if (bIsActive)
    {
        if (!OwnerCharacter->GetStatsComponent()->TryToChangeStatValue(EStatsType::Stamina, -StaminaPerSecond * DeltaTime))
        {
            StopAction(true);
        }
    }

    float& MaxWalkSpeed = OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed;
    float InterpolationSpeed = TargetSpeed > MaxWalkSpeed ? AccelerationSpeed : DecelerationSpeed;
    MaxWalkSpeed = FMath::FInterpTo(MaxWalkSpeed, TargetSpeed, DeltaTime, InterpolationSpeed);
}

bool URunAction::Activate()
{
	if (!IsValid(OwnerCharacter))
	{
		return false;
	}

	if (OwnerCharacter->GetStatsComponent()->GetStatData(EStatsType::Stamina).Value > StaminaToStartRun)
	{   
        if (Super::Activate())
        {
            TargetSpeed = RunSpeed;
            return true;
        }		
	}

	return false;
}

bool URunAction::StopAction(bool bIsForce)
{
	if (Super::StopAction(bIsForce))
	{
        TargetSpeed = DefaultWalkSpeed;		
		return true;
	}

	return false;
}
