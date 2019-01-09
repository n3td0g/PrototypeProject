// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatsComponent.generated.h"

UENUM(BlueprintType)
enum class EStatsType : uint8
{
	Health,
	Stamina,
	Poise,
	Strength,
	PhysicalDefence,
	Power,
	Mana,
	Count	UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FStatData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	EStatsType Type;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Value = 100.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MinValue = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MaxValue = 100.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float DelayBeforeRecovery = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float RecoverySpeed = 0.0f;

	UPROPERTY(Transient)
	float RecoveryStartTime;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONPROJECT_API UCharacterStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatsComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ChangeStatMaxValue(EStatsType Type, float NewMaxValue);

	UFUNCTION(BlueprintCallable)
	void ChangeStatValue(EStatsType Type, float Delta);

    UFUNCTION(BlueprintCallable)
    bool TryToChangeStatValue(EStatsType Type, float Delta);

	UFUNCTION(BlueprintCallable)
	FStatData& GetStatData(EStatsType Type);

	UFUNCTION(BlueprintPure)
	float GetDataValue(EStatsType Type);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditFixedSize, EditAnywhere, Category = Stats)
	TArray<FStatData> Stats;

	TArray<FStatData*> StatsToRecovery;
private:
	void AddToRecoveryList(FStatData& Data);

    void ChangeStatValue(FStatData& Data, float Delta);

	void ChangeStatDataValue(FStatData& Data, float Delta);
};
