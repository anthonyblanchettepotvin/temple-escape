// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#include "OverlappingActorsCondition.h"

#define DEBUG false


bool UOverlappingActorsCondition::Evaluate_Implementation()
{
    TArray<AActor*> OverlappingActors;
    Trigger->GetOverlappingActors(OverlappingActors);

    #if DEBUG
    UE_LOG(LogTemp, Warning, TEXT("UWeightCondition : %i overlapping actors."), OverlappingActors.Num());
    #endif

    return OverlappingActors.Num() == GoalCount ? true : false;
}