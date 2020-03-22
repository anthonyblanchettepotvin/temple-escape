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

    return true;
}

// Getters/setters override
void APuzzlePressurePlate::SetTargetWeightReached(bool Value)
{
    Super::SetTargetWeightReached(Value);

    NotifyPuzzleStateChanged_Implementation();
}
