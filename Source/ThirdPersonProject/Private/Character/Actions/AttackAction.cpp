// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackAction.h"
#include "CharacterActionsComponent.h"
#include "BaseCharacter.h"
#include "BaseWeapon.h"
#include "RunAction.h"

UAttackAction::UAttackAction()
{
    bUseAnimationEvents = true;
    Type = EActionType::Attack;
}

bool UAttackAction::Activate()
{
    CurrentWeapon = OwnerCharacter->GetCurrentWeapon();
    if (IsValid(CurrentWeapon))
    {
        EAttackType AttackType = EAttackType::Default;

        if (IsOnRunAttack())
        {
            AttackType = EAttackType::AfterRun;
        }

        CurrentMontage = CurrentWeapon->GetAttackMontage(AttackType);
        return Super::Activate();
    }
    return false;
}

void UAttackAction::StartAnimationEvent()
{
    Super::StartAnimationEvent();

    CurrentWeapon->StartAttack();
}

void UAttackAction::StopAnimationEvent()
{
    Super::StopAnimationEvent();

    CurrentWeapon->StopAttack();
}

bool UAttackAction::IsOnRunAttack()
{
    if (auto PrevAction = OwnerCharacter->GetActionComponent()->GetPrevAction())
    {
        if (PrevAction->GetActionType() == EActionType::Run)
        {
            if (auto RunAction = Cast<URunAction>(PrevAction))
            {
                if (RunAction->GetIsRunnning())
                {
                    return true;
                }
            }
        }
    }
    return false;
}
