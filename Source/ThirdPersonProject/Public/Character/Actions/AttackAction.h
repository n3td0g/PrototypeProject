// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Actions/BaseMontageAction.h"
#include "AttackAction.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API UAttackAction : public UBaseMontageAction
{
	GENERATED_BODY()
	
public:
    UAttackAction();
	
    virtual bool Activate() override;

protected:
    virtual void StartAnimationEvent() override;
    virtual void StopAnimationEvent() override;

protected:
    UPROPERTY(BlueprintReadOnly)
    class ABaseWeapon* CurrentWeapon;
};
