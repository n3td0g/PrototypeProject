// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeWeapon.h"
#include "DrawDebugHelpers.h"

void AMeleeWeapon::StartAttack(EAttackType AttackType)
{
    Super::StartAttack(AttackType);

    if (!CurrentWeaponAnimation)
    {
        return;
    }

    TraceParams = FCollisionQueryParams();
    TraceParams.AddIgnoredActor(GetOwner());

    UpdatePrevTracePoints();
    GetWorld()->GetTimerManager().SetTimer(TraceTimer, this, &AMeleeWeapon::Trace, TraceUpdateTime, true, TraceUpdateTime);
}

void AMeleeWeapon::StopAttack()
{
    Super::StopAttack();

    GetWorld()->GetTimerManager().ClearTimer(TraceTimer);
}

void AMeleeWeapon::BeginPlay()
{
    Super::BeginPlay();

    auto SceneComponents = GetComponentsByTag(USceneComponent::StaticClass(), ComponentToTraceTag);
    for (auto SceneComponent : SceneComponents)
    {
        if (auto ComponentToTrace = Cast<USceneComponent>(SceneComponent))
        {
            ComponentsToTrace.Add(ComponentToTrace);
        }
    }
}

void AMeleeWeapon::Trace()
{
    if (!CurrentWeaponAnimation)
    {
        return;
    }

    FHitResult HitResult;
    int32 Index = 0;   

    for (auto ComponentToTrace : ComponentsToTrace)
    {
        if (GetWorld()->LineTraceSingleByChannel(HitResult, ComponentToTrace->GetComponentLocation(), PrevTracePoint[Index++], ChannelToTrace, TraceParams))
        {
            if (bDebug)
            {
                ::DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.ImpactPoint, FColor::Green, false, 1.0f);
                ::DrawDebugBox(GetWorld(), HitResult.TraceStart, FVector(5.0f, 5.0f, 5.0f), FColor::Blue);
            }

            if (HitResult.GetActor())
            {
                FPointDamageEvent DamageEvent(CurrentWeaponAnimation->Damage, HitResult, HitResult.ImpactPoint, UDamageType::StaticClass());
                AController* OwnerController = nullptr;
                if (auto Pawn = Cast<APawn>(GetOwner()))
                {
                    OwnerController = Pawn->GetController();
                }
                HitResult.GetActor()->TakeDamage(CurrentWeaponAnimation->Damage, DamageEvent, OwnerController, this);                
                TraceParams.AddIgnoredActor(HitResult.GetActor());
            }
        }
        else
        {
            if (bDebug)
            {
                ::DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor::Red, false, 1.0f);
            }
        }
    }

    UpdatePrevTracePoints();
}

void AMeleeWeapon::UpdatePrevTracePoints()
{
    PrevTracePoint.Empty();
    for (auto ComponentToTrace : ComponentsToTrace)
    {
        PrevTracePoint.Add(ComponentToTrace->GetComponentLocation());
    }
}
