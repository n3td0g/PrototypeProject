// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAction.h"
#include "Components/ActorComponent.h"
#include "CharacterActionsComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONPROJECT_API UCharacterActionsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterActionsComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool StartAction(EActionType NewActionType);

	UFUNCTION(BlueprintCallable)
	bool StopAction(EActionType ActionType);

	bool StopCurrentAction();

	FORCEINLINE UBaseAction* GetCurrentAction() { return CurrentAction; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnStopAction(UBaseAction* Action);

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Actions)
	TArray<TSubclassOf<UBaseAction>> CharacterActionClasses;

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Actions)
    float ActionMemoryTime = 0.75f;

	UPROPERTY(BlueprintReadOnly)
	TMap<EActionType, UBaseAction*> CharacterActions;

	UPROPERTY(BlueprintReadOnly)
	UBaseAction* CurrentAction;

private:
	void CreateActions();

private:
    TArray<UBaseAction*> ActionsToTick;

    EActionType NextAction = EActionType::None;
    float NextActionActivationTime;
};
