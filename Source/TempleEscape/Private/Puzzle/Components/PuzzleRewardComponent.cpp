// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "PuzzleRewardComponent.h"

// Sets default values for this component's properties
UPuzzleRewardComponent::UPuzzleRewardComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UPuzzleRewardComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UPuzzleRewardComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPuzzleRewardComponent::RegisterPuzzle(UPuzzleComponent* Puzzle)
{
	if (!Puzzle) { return; } // TODO: Throw exception ?

    if (!RegisteredPuzzles.Contains(Puzzle))
    {
        RegisteredPuzzles.Add(Puzzle);
    }

    if (bDebug)
    {
        UE_LOG(LogTemp, Warning,
			TEXT("UPuzzleRewardComponent %s - RegisterPuzzle: Puzzle %s registered"),
			*GetOwner()->GetName(),
			*Puzzle->GetOwner()->GetName())
    }
}

void UPuzzleRewardComponent::UnregisterPuzzle(UPuzzleComponent* Puzzle)
{
	if (!Puzzle) { return; } // TODO: Throw exception ?

    if (RegisteredPuzzles.Contains(Puzzle))
    {
        RegisteredPuzzles.Remove(Puzzle);
    }

    if (bDebug)
    {
        UE_LOG(LogTemp, Warning,
			TEXT("UPuzzleRewardComponent %s - UnregisterPuzzle: Puzzle %s Unregistered"),
			*GetOwner()->GetName(),
			*Puzzle->GetOwner()->GetName())
    }
}
