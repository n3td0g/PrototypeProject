#include "CharacterActionsComponent.h"

UCharacterActionsComponent::UCharacterActionsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCharacterActionsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    for (auto ActionToTick : ActionsToTick)
    {
        ActionToTick->ActionTick(DeltaTime);
    }

    if (!CurrentAction)
    {
        if (NextAction != EActionType::None)
        {
            EActionType NewActionType = NextAction;
            NextAction = EActionType::None;
            if (GetWorld()->TimeSeconds - NextActionActivationTime < ActionMemoryTime)
            {
                StartAction(NewActionType);
            }
        }
    }
}

bool UCharacterActionsComponent::StartAction(EActionType NewActionType)
{
	auto NewActionPtr = CharacterActions.Find(NewActionType);
	if (!NewActionPtr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Action type <%s> not found."), *UBaseAction::GetActionTypeAsString(NewActionType));
		return false;
	}

	auto NewAction = *NewActionPtr;
	if (!IsValid(NewAction))
	{
		UE_LOG(LogTemp, Warning, TEXT("Action <%s> is not valid."), *UBaseAction::GetActionTypeAsString(NewActionType));
		return false;
	}

	if (IsValid(CurrentAction))
	{
		if (!NewAction->HasHigherPriority(CurrentAction->GetActionType()))
		{
            NextAction = NewActionType;
            NextActionActivationTime = GetWorld()->TimeSeconds;
			return false;
		}

		CurrentAction->StopAction(true);
	}

	if (NewAction->Activate())
	{
		CurrentAction = NewAction;
		CurrentAction->OnStopAction.AddDynamic(this, &UCharacterActionsComponent::OnStopAction);
        if (CurrentAction->GetTickOnlyIfActive())
        {
            ActionsToTick.Push(CurrentAction);
        }
        //If action was stopped in function Activate()
        if (!CurrentAction->GetIsActive())
        {
            StopCurrentAction();
        }
	}
	else
	{
		CurrentAction = nullptr;
	}

	return true;
}

bool UCharacterActionsComponent::StopAction(EActionType ActionType)
{
	if (IsValid(CurrentAction))
	{
		if (CurrentAction->GetActionType() == ActionType)
		{
			return StopCurrentAction();
		}
	}
	return false;
}

bool UCharacterActionsComponent::StopCurrentAction()
{
	if (IsValid(CurrentAction))
	{
		return CurrentAction->StopAction(false);
	}
	return false;
}

void UCharacterActionsComponent::BeginPlay()
{
	Super::BeginPlay();

	CreateActions();
}

void UCharacterActionsComponent::OnStopAction(UBaseAction* Action)
{
	if (Action == CurrentAction)
	{
		if (IsValid(CurrentAction))
		{
			CurrentAction->OnStopAction.RemoveDynamic(this, &UCharacterActionsComponent::OnStopAction);
            if (CurrentAction->GetTickOnlyIfActive())
            {
                ActionsToTick.Remove(CurrentAction);
            }
		}

		CurrentAction = nullptr;
	}
}

void UCharacterActionsComponent::CreateActions()
{
	for (auto ActionClass : CharacterActionClasses)
	{
		if (ActionClass)
		{
			if (auto ActionDefaultObject = ActionClass->GetDefaultObject<UBaseAction>())
			{
				if (CharacterActions.Contains(ActionDefaultObject->GetActionType()))
				{
					UE_LOG(LogTemp, Warning, TEXT("Action type <%s> is already exist."), *UBaseAction::GetActionTypeAsString(ActionDefaultObject->GetActionType()));
					continue;
				}

				if (ActionDefaultObject->GetActionType() == EActionType::None)
				{
					UE_LOG(LogTemp, Warning, TEXT("Action type in None."));
					continue;
				}
			}

			auto NewAction = NewObject<UBaseAction>(this, ActionClass);
			NewAction->SetOwner(GetOwner());
			NewAction->Init();
			CharacterActions.Add(NewAction->GetActionType(), NewAction);
            if (!NewAction->GetTickOnlyIfActive())
            {
                ActionsToTick.Push(NewAction);
            }
		}
	}
}

