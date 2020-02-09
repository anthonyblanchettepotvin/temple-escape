// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#include "DoorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define DEBUG false


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
			InitialRotation = GetOwner()->GetActorRotation();

			#if DEBUG
			UE_LOG(LogTemp, Warning, TEXT("OpenDoor on %s : Door opened."), *GetOwner()->GetName());
			#endif
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
			InitialRotation = GetOwner()->GetActorRotation();

			#if DEBUG
			UE_LOG(LogTemp, Warning, TEXT("OpenDoor on %s : Door closed."), *GetOwner()->GetName());
			#endif
		}

		return;
	}
}


bool UDoorComponent::IsOpen() const
{
	return bIsOpen;
}


bool UDoorComponent::IsOpening() const
{
	return bIsOpening;
}


bool UDoorComponent::IsClosing() const
{
	return bIsClosing;
}


void UDoorComponent::OpenDoor()
{
	InitialRotation = GetOwner()->GetActorRotation();

	float Distance = FVector::Distance(OpenRotation.Vector(), CloseRotation.Vector());
	float DistanceLeft = FVector::Distance(InitialRotation.Vector(), CloseRotation.Vector());
	float Delta = DistanceLeft / Distance * OpenDuration;
	ElapsedTime = Delta;

	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("OpenDoor on %s : Open door."), *GetOwner()->GetName());
	#endif

	bIsOpening = true;
	bIsClosing = false;
}


void UDoorComponent::OpenDoorMovement(const float DeltaTime)
{
	ElapsedTime += DeltaTime;

	CurrentRotation = FMath::Lerp(CloseRotation, OpenRotation, ElapsedTime / OpenDuration);

	GetOwner()->SetActorRotation(CurrentRotation);
}


void UDoorComponent::CloseDoor()
{
	InitialRotation = GetOwner()->GetActorRotation();

	float Distance = FVector::Distance(CloseRotation.Vector(), OpenRotation.Vector());
	float DistanceLeft = FVector::Distance(InitialRotation.Vector(), OpenRotation.Vector());
	float Delta = DistanceLeft / Distance * CloseDuration;
	ElapsedTime = Delta;

	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("OpenDoor on %s : Close door."), *GetOwner()->GetName());
	#endif

	bIsClosing = true;
	bIsOpening = false;
}


void UDoorComponent::CloseDoorMovement(const float DeltaTime)
{
	ElapsedTime += DeltaTime;

	CurrentRotation = FMath::Lerp(OpenRotation, CloseRotation, ElapsedTime / CloseDuration);

	GetOwner()->SetActorRotation(CurrentRotation);
}
