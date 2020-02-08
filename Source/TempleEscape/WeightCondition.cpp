// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#include "WeightCondition.h"

#define DEBUG false


UWeightCondition::UWeightCondition()
{
}


UWeightCondition::~UWeightCondition()
{
}


bool UWeightCondition::Evaluate_Implementation()
{
    float TotalMass = 0.0f;

    TArray<AActor*> OverlappingActors;
    Trigger->GetOverlappingActors(OverlappingActors);
    UPrimitiveComponent* Prim = nullptr;
    

    for (int32 i = 0; i < OverlappingActors.Num(); i++)
    {
        #if DEBUG
        UE_LOG(LogTemp, Warning, TEXT("UWeightCondition : %s overlapping."), *OverlappingActors[i]->GetName());
        #endif

        Prim = OverlappingActors[i]->FindComponentByClass<UPrimitiveComponent>();
        if (Prim) { 
            if (Prim->IsSimulatingPhysics()) { TotalMass += Prim->GetMass(); }
        }
    }

    return TotalMass >= GoalMass ? true : false;
}
