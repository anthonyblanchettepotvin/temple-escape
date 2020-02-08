// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#include "PuzzleDoorComponent.h"
#include "DoorComponent.h"


// Sets default values for this component's properties
UPuzzleDoorComponent::UPuzzleDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPuzzleDoorComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UPuzzleDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ConditionsMet_Implementation();
}


void UPuzzleDoorComponent::Interact()
{
	if (bUnlocked)
	{
		Super::Interact();
	}
}


bool UPuzzleDoorComponent::ConditionsMet_Implementation()
{
	if (Conditions.Num() == 0) { return true; }

	for (int32 i = 0; i < Conditions.Num(); i++)
	{
		if (!Conditions[i]->Evaluate())
		{
			if (bConditionsMet)
			{
				bConditionsMet = false;
				OnConditionsUnmet_Implementation();
			}
			return false;
		}
	}
	
	if (!bConditionsMet)
	{
		bConditionsMet = true;
		OnConditionsMet_Implementation();
	}
	return true;
}


void UPuzzleDoorComponent::OnConditionsMet_Implementation()
{
	bUnlocked = true;

	OpenDoor();
}


void UPuzzleDoorComponent::OnConditionsUnmet_Implementation()
{
	bUnlocked = false;

	CloseDoor();
}
