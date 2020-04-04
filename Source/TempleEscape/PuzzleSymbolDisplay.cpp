// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "PuzzleSymbolDisplay.h"

// Getters/setters
void APuzzleSymbolDisplay::SetTargetSymbol(ESymbol Value)
{
    TargetSymbol = Value;
}

ESymbol APuzzleSymbolDisplay::GetTargetSymbol()
{
    return TargetSymbol;
}

// Functions
bool APuzzleSymbolDisplay::IsSymbolOnTarget()
{
    return GetCurrentSymbol() == GetTargetSymbol();
}

// Getters/setters override
void APuzzleSymbolDisplay::SetCurrentSymbol(ESymbol Value)
{
    Super::SetCurrentSymbol(Value);

    NotifyPuzzleStateChanged_Implementation();
}

// IPuzzleCondition implementation
bool APuzzleSymbolDisplay::Evaluate_Implementation()
{
    return IsSymbolOnTarget();
}

bool APuzzleSymbolDisplay::NotifyPuzzleStateChanged_Implementation()
{
    for (AActor* RegisteredPuzzle : RegisteredPuzzles)
    {
        IPuzzle::Execute_ConditionStateChanged(RegisteredPuzzle, this, IsSymbolOnTarget());

        if (bDebug)
        {
            UE_LOG(LogTemp, Warning, TEXT("APuzzleSymbolDisplay %s: Puzzle %s notified"), *GetName(), *RegisteredPuzzle->GetName())
        }
    }

    return true;
}

bool APuzzleSymbolDisplay::RegisterPuzzle_Implementation(AActor* Puzzle)
{
    bool bImplementsInterface = Puzzle->GetClass()->ImplementsInterface(UPuzzle::StaticClass());
    if (!bImplementsInterface) { return false; }

    if (!RegisteredPuzzles.Contains(Puzzle))
    {
        RegisteredPuzzles.Add(Puzzle);
    }

    if (bDebug)
    {
        UE_LOG(LogTemp, Warning, TEXT("APuzzleSymbolDisplay %s: Puzzle %s registered"), *GetName(), *Puzzle->GetName())
    }
    
    return true;
}

bool APuzzleSymbolDisplay::UnregisterPuzzle_Implementation(AActor* Puzzle)
{
    bool bImplementsInterface = Puzzle->GetClass()->ImplementsInterface(UPuzzle::StaticClass());
    if (!bImplementsInterface) { return false; }

    if (RegisteredPuzzles.Contains(Puzzle))
    {
        RegisteredPuzzles.Remove(Puzzle);
    }

    if (bDebug)
    {
        UE_LOG(LogTemp, Warning, TEXT("APuzzleSymbolDisplay %s: Puzzle %s unregistered"), *GetName(), *Puzzle->GetName())
    }
    
    return true;
}
