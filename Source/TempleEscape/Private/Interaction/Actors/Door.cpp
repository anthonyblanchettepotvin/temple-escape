// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "Door.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	LeftDoor = CreateDefaultSubobject<UDoorComponent>(TEXT("LeftDoor"));
	LeftDoor->SetMobility(EComponentMobility::Movable);
	LeftDoor->SetCollisionProfileName("Interactable");
	LeftDoor->SetupAttachment(Root);

	RightDoor = CreateDefaultSubobject<UDoorComponent>(TEXT("RightDoor"));
	RightDoor->SetMobility(EComponentMobility::Movable);
	RightDoor->SetCollisionProfileName("Interactable");
	RightDoor->SetupAttachment(Root);

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
	FrameMesh->SetMobility(EComponentMobility::Movable);
	FrameMesh->SetupAttachment(Root);

	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	Audio->SetupAttachment(Root);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Functions
void ADoor::OpenDoor()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADoor %s: Open door"), *GetName());
	}

	if (LeftDoor)
	{
		LeftDoor->OpenDoor();
	}

	if (RightDoor)
	{
		RightDoor->OpenDoor();
	}

	PlayOpenSound();
}

void ADoor::CloseDoor()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADoor %s: Close door"), *GetName());
	}

	if (LeftDoor)
	{
		LeftDoor->CloseDoor();
	}

	if (RightDoor)
	{
		RightDoor->CloseDoor();
	}

	PlayCloseSound();
}

void ADoor::UnlockDoor()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADoor %s: Unlock door"), *GetName());
	}

	if (LeftDoor)
	{
		LeftDoor->UnlockDoor();
	}

	if (RightDoor)
	{
		RightDoor->UnlockDoor();
	}

	OnDoorUnlocked();
}

void ADoor::LockDoor()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADoor %s: Lock door"), *GetName());
	}

	if (LeftDoor)
	{
		LeftDoor->LockDoor();
	}

	if (RightDoor)
	{
		RightDoor->LockDoor();
	}

	OnDoorLocked();
}

void ADoor::PlayOpenSound() const
{
	if (!Audio) { return; }

	if (!OpenDoorSound) 
	{
		UE_LOG(LogTemp, Error, TEXT("ADoor %s: Open Door Sound is missing!"), *GetName());
		return;
	}

	Audio->SetSound(OpenDoorSound);
	Audio->Play();
}

void ADoor::PlayCloseSound() const
{
	if (!Audio) { return; }

	if (!CloseDoorSound) 
	{
		UE_LOG(LogTemp, Error, TEXT("Door %s : Close Door Sound is missing!"), *GetName());
		return;
	}

	Audio->SetSound(CloseDoorSound);
	Audio->Play();
}

// Events
void ADoor::OnDoorOpened_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADoor %s: OnDoorOpened"), *GetName());
	}
}

void ADoor::OnDoorClosed_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADoor %s: OnDoorClosed"), *GetName());
	}
}

void ADoor::OnDoorUnlocked_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADoor %s: OnDoorUnlocked"), *GetName());
	}
}

void ADoor::OnDoorLocked_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADoor %s: OnDoorLocked"), *GetName());
	}
}

// IInteractable implementation
bool ADoor::Interact_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADoor %s: Interact"), *GetName());
	}

	if (LeftDoor)
	{
		LeftDoor->OpenCloseDoor();
	}

	if (RightDoor)
	{
		RightDoor->OpenCloseDoor();
	}

	return true;
}
