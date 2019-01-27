// Fill out your copyright notice in the Description page of Project Settings.

#include "StartActionAsync.h"
#include "BaseCharacter.h"
#include "CharacterActionsComponent.h"


UStartActionAsync* UStartActionAsync::StartActionAsync(UObject* WorldContextObject, class ABaseCharacter* InCharacter, EActionType InActionType)
{
    UStartActionAsync* Action = NewObject<UStartActionAsync>();
    Action->Character = InCharacter;
    Action->ActionType = InActionType;
    return Action;
}

void UStartActionAsync::Activate()
{
    if (!IsValid(Character))
    {
        OnFailed.Broadcast();
        return;
    }

    auto ActionComponent = Character->GetActionComponent();

    if (!IsValid(ActionComponent))
    {
        OnFailed.Broadcast();
        return;
    }

    if (ActionComponent->StartAction(ActionType))
    {
        ActionComponent->OnActionStopped.AddDynamic(this, &UStartActionAsync::OnActionStopped);
    }
}

void UStartActionAsync::OnActionStopped(UBaseAction* Action)
{
    auto ActionComponent = Character->GetActionComponent();
    ActionComponent->OnActionStopped.RemoveDynamic(this, &UStartActionAsync::OnActionStopped);
    OnSuccess.Broadcast();
}

