// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAction.h"
#include "UObject/UObjectGlobals.h"
#include "BaseCharacter.h"
#include "Bitmask.h"

bool UBaseAction::HasHigherPriority(EActionType PrevActionType)
{
	return TEST_BIT(ActionsThatCanBeBraked, PrevActionType);
}

void UBaseAction::Init()
{
	ReceiveInit();
}

void UBaseAction::ActionTick(float DeltaTime)
{
	ReceiveTick(DeltaTime);
}

bool UBaseAction::Activate()
{
    if (ReceiveActivate())
    {
        bIsActive = true;
        return true;
    }
    return false;
}

bool UBaseAction::ReceiveActivate_Implementation()
{
    return true;
}

bool UBaseAction::StopAction(bool bIsForce)
{
	if (ReceiveStopAction(bIsForce))
	{
		OnStopAction.Broadcast(this);
        bIsActive = false;
		return true;
	}
	return false;
}

bool UBaseAction::ReceiveStopAction_Implementation(bool bIsForce)
{
	return true;
}

void UBaseAction::SetOwner(AActor* Owner)
{
	OwnerCharacter = Cast<ABaseCharacter>(Owner);
}

FString UBaseAction::GetActionTypeAsString(EActionType ActionType)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EActionType"), true);
	if (!EnumPtr) return FString("Invalid");

	return EnumPtr->GetNameByValue((int64)ActionType).ToString();
}
