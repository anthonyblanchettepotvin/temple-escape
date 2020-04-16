// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "PuzzleComponent.h"

// Sets default values for this component's properties
UPuzzleComponent::UPuzzleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPuzzleComponent::BeginPlay()
{
	Super::BeginPlay();

	bConditionsOK = CheckConditionsImplementation();
	bRewardsOK = CheckRewardsImplementation();

	if (!bConditionsOK)
	{
		UE_LOG(LogTemp, Error, TEXT("UPuzzleComponent %s: Not all conditions implement IPuzzleCondition."), *GetName());
	}

	if (!bRewardsOK)
	{
		UE_LOG(LogTemp, Error, TEXT("UPuzzleComponent %s: Not all rewards implement IPuzzleReward."), *GetName());
	}

	if (Trigger)
	{
		if (!SubscribeToTrigger(Trigger))
		{
			UE_LOG(LogTemp, Error, TEXT("UPuzzleComponent %s: Could not subscribe to Trigger."), *GetName());
		}
	}

	if (bConditionsOK)
	{
		for (AActor* Condition : Conditions)
		{
			IPuzzleCondition::Execute_RegisterPuzzle(Condition, this);
		}
	}
}


// Called every frame
void UPuzzleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UPuzzleComponent::CheckConditionsImplementation()
{
	for (AActor* Condition : Conditions)
	{
		bool bImplementsInterface = Condition->GetClass()->ImplementsInterface(UPuzzleCondition::StaticClass());
		if (!bImplementsInterface)
		{
			return false;
		}
	}

	return true;	
}

bool UPuzzleComponent::CheckRewardsImplementation()
{
	for (AActor* Reward : Rewards)
	{
		bool bImplementsInterface = Reward->GetClass()->ImplementsInterface(UPuzzleReward::StaticClass()); 
		if (!bImplementsInterface)
		{
			return false;
		}
	}

	return true;
}

void UPuzzleComponent::UnlockAllRewards()
{
	for (AActor* Reward : Rewards)
	{
		// We already know that all the actors implement the necessary interface(s)
		IPuzzleReward::Execute_UnlockReward(Reward);
	}
}

void UPuzzleComponent::LockAllRewards()
{
	for (AActor* Reward : Rewards)
	{
		// We already know that all the actors implement the necessary interface(s)
		IPuzzleReward::Execute_LockReward(Reward);
	}
}

void UPuzzleComponent::ActOnConditionsMet()
{
	bool bConditionsAlreadyMet = bConditionsMet;
	bConditionsMet = AreConditionsMet();

	if (bConditionsMet && !bConditionsAlreadyMet)
	{
		// The conditions turned from met to unmet
		bConditionsAlreadyMet = true;
		OnConditionsMet();

		UnlockAllRewards();

		return;
	}

	if (!bConditionsMet && bConditionsAlreadyMet)
	{
		// The conditions turned from unmet to met
		bConditionsAlreadyMet = false;
		OnConditionsUnmet();

		if (!bUnlockRewardsPermanently)
		{
			LockAllRewards();
		}

		return;
	}
}

bool UPuzzleComponent::AreConditionsMet()
{
	if (!bConditionsOK || !bRewardsOK) { return false; }

	for (AActor* Condition : Conditions)
	{
		// We already know that all the actors implement the necessary interface(s)
		if (!IPuzzleCondition::Execute_Evaluate(Condition))
		{
			return false;
		}
	}

	return true;
}

bool UPuzzleComponent::ConditionStateChanged(AActor* Condition, bool State)
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPuzzleComponent %s: Condition %s state changed to %s"),
			*GetName(),
			*Condition->GetName(),
			State ? TEXT("true") : TEXT("false"))
	}

	if (!Trigger || !State) { ActOnConditionsMet(); }

	return true;
}

bool UPuzzleComponent::ReactToTrigger()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPuzzleComponent %s: Triggered"), *GetName())
	}

	ActOnConditionsMet();

	return true;
}

bool UPuzzleComponent::SubscribeToTrigger(UObject* wTrigger)
{
	bool bImplementsInterface = wTrigger->GetClass()->ImplementsInterface(UPuzzleTrigger::StaticClass());
	if (bImplementsInterface)
	{
		// FIXME: return IPuzzleTrigger::Execute_Subscribe(Trigger, this);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UPuzzleComponent %s: Trigger %s doesn't implement IPuzzleTrigger"), *GetName(), *wTrigger->GetName())
		return false;
	}
}

bool UPuzzleComponent::UnsubscribeFromTrigger(UObject* wTrigger)
{
	bool bImplementsInterface = wTrigger->GetClass()->ImplementsInterface(UPuzzleTrigger::StaticClass());
	if (bImplementsInterface)
	{
		// FIXME: return IPuzzleTrigger::Execute_Unsubscribe(Trigger, this);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UPuzzleComponent %s: Trigger %s doesn't implement IPuzzleTrigger"), *GetName(), *wTrigger->GetName())
		return false;
	}
}

// Events
void UPuzzleComponent::OnConditionsMet_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPuzzleComponent %s: OnConditionsMet"), *GetName())
	}
}

void UPuzzleComponent::OnConditionsUnmet_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPuzzleComponent %s: OnConditionsUnmet"), *GetName())
	}
}
