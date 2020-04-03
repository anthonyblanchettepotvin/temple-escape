// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "PuzzlePressurePlate.h"

// IPuzzleCondition implementation
bool APuzzlePressurePlate::Evaluate_Implementation()
{
    return GetTargetWeightReached();
}

bool APuzzlePressurePlate::NotifyPuzzleStateChanged_Implementation()
{
    for (AActor* RegisteredPuzzle : RegisteredPuzzles)
    {
        IPuzzle::Execute_ConditionStateChanged(RegisteredPuzzle, this, GetTargetWeightReached());
    }

    if (bDebug)
    {
        UE_LOG(LogTemp, Warning, TEXT("APuzzlePressurePlate %s: Puzzle %s notified"), *GetName(), *Puzzle->GetName())
    }

    return true;
}

bool APuzzlePressurePlate::RegisterPuzzle_Implementation(AActor* Puzzle)
{
    bool bImplementsInterface = Puzzle->GetClass()->ImplementsInterface(UPuzzle::StaticClass());
    if (!bImplementsInterface) { return false; }

    if (!RegisteredPuzzles.Contains(Puzzle))
    {
        RegisteredPuzzles.Add(Puzzle);
    }

    if (bDebug)
    {
        UE_LOG(LogTemp, Warning, TEXT("APuzzlePressurePlate %s: Puzzle %s registered"), *GetName(), *Puzzle->GetName())
    }

    return true;
}

bool APuzzlePressurePlate::UnregisterPuzzle_Implementation(AActor* Puzzle)
{
    bool bImplementsInterface = Puzzle->GetClass()->ImplementsInterface(UPuzzle::StaticClass());
    if (!bImplementsInterface) { return false; }

    if (RegisteredPuzzles.Contains(Puzzle))
    {
        RegisteredPuzzles.Remove(Puzzle);
    }

    if (bDebug)
    {
        UE_LOG(LogTemp, Warning, TEXT("APuzzlePressurePlate %s: Puzzle %s unregistered"), *GetName(), *Puzzle->GetName())
    }

    return true;
}

// Getters/setters override
void APuzzlePressurePlate::SetTargetWeightReached(bool Value)
{
    Super::SetTargetWeightReached(Value);

    NotifyPuzzleStateChanged_Implementation();
}
