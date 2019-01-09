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
	
}
