// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "CharacterActionsComponent.h"
#include "CharacterStatsComponent.h"
#include "BaseWeapon.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ActionComponent = CreateDefaultSubobject<UCharacterActionsComponent>("ActionComponent");
	StatsComponent = CreateDefaultSubobject<UCharacterStatsComponent>("StatsComponent");
}

float ABaseCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
    
    if (StatsComponent->ChangeStatValue(EStatsType::Health, -ActualDamage) <= 0.0f)
    {
        ActionComponent->StartAction(EActionType::Death);
    }
    return ActualDamage;
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ABaseWeapon* ABaseCharacter::GetCurrentWeapon()
{
    if (!IsValid(TestWeapon))
    {
        if (TestWeaponClass)
        {
            FActorSpawnParameters Params;
            Params.Owner = this;
            Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
            TestWeapon = GetWorld()->SpawnActor<ABaseWeapon>(TestWeaponClass, Params);
            TestWeapon->Equip(GetMesh());
        }
    }

    return TestWeapon;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    GetCurrentWeapon();
}
