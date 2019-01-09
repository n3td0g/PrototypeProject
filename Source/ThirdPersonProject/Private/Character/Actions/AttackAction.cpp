// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackAction.h"
#include "BaseCharacter.h"
#include "BaseWeapon.h"

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
        CurrentMontage = CurrentWeapon->GetAttackMontage(EAttackType::Default);
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
