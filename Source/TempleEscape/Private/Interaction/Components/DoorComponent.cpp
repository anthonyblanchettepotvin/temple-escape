// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "DoorComponent.h"

// Sets default values for this component's properties
UDoorComponent::UDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UDoorComponent::BeginPlay()
{
	Super::BeginPlay();

	CloseRotation = GetRelativeRotation();
	OpenRotation = GetRelativeRotation() + AnimationAmount;
}

// Called every frame
void UDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsOpening && !bIsClosing) { return; }

	if (bIsOpening)
	{
		OpenDoorMovement(DeltaTime);

		if (ElapsedTime > OpenDuration)
		{
			bIsOpening = false;
			bIsOpen = true;
			ElapsedTime = 0.0f;

			//OnDoorOpened();
		}

		return;
	}

	if (bIsClosing)
	{
		CloseDoorMovement(DeltaTime);

		if (ElapsedTime > CloseDuration)
		{
			bIsClosing = false;
			bIsOpen = false;
			ElapsedTime = 0.0f;

			//OnDoorClosed();
		}

		return;
	}
}

// Functions
void UDoorComponent::OpenDoor()
{
	ElapsedTime = CalculateAnimationProgress(CloseRotation, OpenRotation, GetRelativeRotation()) * OpenDuration;

	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADoor %s: Open door"), *GetName());
	}

	bIsOpening = true;
	bIsClosing = false;
}

void UDoorComponent::OpenDoorMovement(const float DeltaTime)
{
	ElapsedTime += DeltaTime;

	FRotator NewRotation = FMath::Lerp(CloseRotation, OpenRotation, ElapsedTime / OpenDuration);

	SetRelativeRotation(NewRotation);
}

void UDoorComponent::CloseDoor()
{
	ElapsedTime = CalculateAnimationProgress(OpenRotation, CloseRotation, GetRelativeRotation()) * CloseDuration;

	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADoor %s: Close door"), *GetName());
	}

	bIsClosing = true;
	bIsOpening = false;
}

void UDoorComponent::CloseDoorMovement(const float DeltaTime)
{
	ElapsedTime += DeltaTime;

	FRotator NewRotation = FMath::Lerp(OpenRotation, CloseRotation, ElapsedTime / CloseDuration);

	SetRelativeRotation(NewRotation);
}

void UDoorComponent::OpenCloseDoor()
{
	if (!bIsUnlocked) { return; }

	if (bIsOpening)
	{
		CloseDoor();
	}
	else if (bIsClosing)
	{
		OpenDoor();
	}
	else if (bIsOpen)
	{
		CloseDoor();
	}
	else
	{
		OpenDoor();
	}
}

void UDoorComponent::UnlockDoor()
{
	if (!bIsOpen || bIsClosing)
	{
		OpenDoor();
	}

	if (bIsUnlocked) { return; }

	bIsUnlocked = true;
	//OnDoorUnlocked();
}

void UDoorComponent::LockDoor()
{
	if (bIsOpen || bIsOpening)
	{
		CloseDoor();
	}

	if (!bIsUnlocked) { return; }

	bIsUnlocked = false;
	//OnDoorLocked();
}

float UDoorComponent::CalculateAnimationProgress(const FRotator& StartRotation, const FRotator& EndRotation, const FRotator& CurrentRotation) const
{
	float CompleteAnimationRotation = FVector::Distance(StartRotation.Euler(), EndRotation.Euler());
	float AnimationRotationLeft = FVector::Distance(CurrentRotation.Euler(), EndRotation.Euler());
	float Progress = 1 - (AnimationRotationLeft / CompleteAnimationRotation);

	return Progress;
}
