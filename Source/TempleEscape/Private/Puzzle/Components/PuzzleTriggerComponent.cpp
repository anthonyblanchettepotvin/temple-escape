// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "PuzzleTriggerComponent.h"

// Sets default values for this component's properties
UPuzzleTriggerComponent::UPuzzleTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UPuzzleTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UPuzzleTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPuzzleTriggerComponent::NotifyTriggered()
{
    for (UPuzzleComponent* Puzzle : RegisteredPuzzles)
    {
        if (!Puzzle) {
            UE_LOG(LogTemp, Error,
				TEXT("UPuzzleComponent %s - NotifyTriggered: Puzzle is None (ignored)"),
				*GetOwner()->GetName())
            
            continue;
        }

		Puzzle->TriggerTriggered(this);

        if (bDebug)
        {
            UE_LOG(LogTemp, Warning,
				TEXT("APuzzleButton %s - NotifyTriggered: Puzzle %s notified"),
				*GetOwner()->GetName(),
				*Puzzle->GetOwner()->GetName())
        }
    }
}

void UPuzzleTriggerComponent::RegisterPuzzle(UPuzzleComponent* Puzzle)
{
	if (!Puzzle) { return; } // TODO: Throw exception ?

    if (!RegisteredPuzzles.Contains(Puzzle))
    {
        RegisteredPuzzles.Add(Puzzle);
    }

    if (bDebug)
    {
        UE_LOG(LogTemp, Warning,
			TEXT("APuzzleButton %s - RegisterPuzzle: Puzzle %s registered"),
			*GetOwner()->GetName(),
			*Puzzle->GetOwner()->GetName())
    }
}

void UPuzzleTriggerComponent::UnregisterPuzzle(UPuzzleComponent* Puzzle)
{
	if (!Puzzle) { return; } // TODO: Throw exception ?

    if (RegisteredPuzzles.Contains(Puzzle))
    {
        RegisteredPuzzles.Remove(Puzzle);
    }

    if (bDebug)
    {
        UE_LOG(LogTemp, Warning,
			TEXT("APuzzleButton %s - UnregisterPuzzle: Puzzle %s Unregistered"),
			*GetOwner()->GetName(),
			*Puzzle->GetOwner()->GetName())
    }
}
