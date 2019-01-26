// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseAction.generated.h"

class ACharacter;

UENUM(BlueprintType, meta = (Bitflags))
enum class EActionType : uint8
{
	None,
	Run,
	Jump,
	Backstep,
	Roll,
	Attack,
	Kick,
	UseSelectedItem,
	UseSpell,
	Backstab,
	CriticalDamage,
	Block,
	Stagger,
	StunLock,
	Interact,
	Death
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStopActionSignature, UBaseAction*, Action);

class ABaseCharacter;

/**
 * 
 */
UCLASS(Blueprintable)
class THIRDPERSONPROJECT_API UBaseAction : public UObject
{
	GENERATED_BODY()
	
public:
	bool HasHigherPriority(EActionType PrevActionType);

    virtual UWorld* GetWorld() const override;
	virtual void Init();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Init"))
	void ReceiveInit();

	virtual void ActionTick(float DeltaTime);
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Tick"))
	void ReceiveTick(float DeltaTime);

	virtual bool Activate();

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Activate"))
	bool ReceiveActivate();
	
	virtual bool StopAction(bool bIsForce);

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "StopAction"))
	bool ReceiveStopAction(bool bIsForce);

    virtual bool ContinueAction();

	void SetOwner(AActor* Owner);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EActionType GetActionType() const { return Type; }

    FORCEINLINE bool GetIsActive() { return bIsActive; }

    FORCEINLINE bool GetTickOnlyIfActive() { return bTickOnlyIfActive; }

	static FString GetActionTypeAsString(EActionType ActionType);

	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnStopActionSignature OnStopAction;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Action)
	EActionType Type = EActionType::None;

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Action)
    bool bTickOnlyIfActive = true;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Action, meta = (Bitmask, BitmaskEnum = "EActionType"))
	int32 ActionsThatCanBeBraked;

	UPROPERTY(BlueprintReadOnly)
	ABaseCharacter* OwnerCharacter;

    UPROPERTY(BlueprintReadOnly)
    bool bIsActive;

private:
    virtual bool CanBeStopped();
};
