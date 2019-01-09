// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UCharacterActionsComponent;
class UCharacterStatsComponent;
class ABaseWeapon;

UCLASS()
class THIRDPERSONPROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

public:
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UCharacterActionsComponent* GetActionComponent() { return ActionComponent;  }
	FORCEINLINE UCharacterStatsComponent* GetStatsComponent() { return StatsComponent; }

    UFUNCTION(BlueprintCallable)
    ABaseWeapon* GetCurrentWeapon();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)
	UCharacterActionsComponent* ActionComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)
	UCharacterStatsComponent* StatsComponent;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Weapons)
    TSubclassOf<ABaseWeapon> TestWeaponClass;

    UPROPERTY(BlueprintReadOnly)
    ABaseWeapon* TestWeapon;
};
