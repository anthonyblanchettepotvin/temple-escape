// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "PuzzleButton.h"

bool APuzzleButton::Evaluate_Implementation()
{
    return bIsPressed;
}

void APuzzleButton::Press()
{
    Super::Press();

    Execute_Trigger(this);
}

bool APuzzleButton::Interact_Implementation()
{
    Super::Interact_Implementation();
    
    for (auto &&AjdacentButton : AdjacentButtons)
    {
        if (AjdacentButton->bIsPressed)
        {
            AjdacentButton->Unpress();
        }
        else
        {
            AjdacentButton->Press();
        }
    }
    
    return true;
}



bool APuzzleButton::Trigger_Implementation()
{
    if (bDebug)
    {
        UE_LOG(LogTemp, Warning, TEXT("APuzzleButton %s: Triggered."), *GetName())
    }

    // Call EvaluatePuzzleState() on every subscribed puzzle
    for (AActor* Puzzle : SubscribedPuzzles)
    {
        IPuzzle::Execute_Trigger(Puzzle);
    }

    return true;
}

bool APuzzleButton::Subscribe_Implementation(AActor* Puzzle)
{
    if (Puzzle->GetClass()->ImplementsInterface(UPuzzle::StaticClass()))
    {
        SubscribedPuzzles.Add(Puzzle);
    }

    return true;
}

bool APuzzleButton::Unsubscribe_Implementation(AActor* Puzzle)
{
    if (SubscribedPuzzles.Contains(Puzzle))
    {
        SubscribedPuzzles.Remove(Puzzle);
    }

    return true;
}