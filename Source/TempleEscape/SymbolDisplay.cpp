// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "SymbolDisplay.h"

ASymbolDisplay::ASymbolDisplay()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SymbolDisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SymbolDisplay"));
	SymbolDisplayMesh->SetMobility(EComponentMobility::Movable);
	SymbolDisplayMesh->SetCollisionProfileName("Interactable");
	SymbolDisplayMesh->SetupAttachment(Root);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	BaseMesh->SetMobility(EComponentMobility::Movable);
	BaseMesh->SetupAttachment(Root);
}

void ASymbolDisplay::BeginPlay()
{
	Super::BeginPlay();

	OffsetRotation = { 0.0f, 360 / (uint8)ESymbol::S_Count, 0.0f};

	SetNextTargetRotation(GetCurrentSymbolByte());

	SymbolDisplayMesh->SetRelativeRotation(TargetRotation);

	SetNextTargetRotation();

	SetIsOnTarget(IsSymbolOnTarget());
}

void ASymbolDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsTurning) { return; }

	if (bIsTurning)
	{
		TurningAnimation(DeltaTime);

		if (ElapsedTime >= TurnDuration)
		{
			bIsTurning = false;
			ElapsedTime = 0.0f;

			SetNextTargetRotation();

			ESymbol NewSymbol = static_cast<ESymbol>((GetCurrentSymbolByte() + 1) % (uint8)ESymbol::S_Count);
			SetCurrentSymbol(NewSymbol);
			SetIsOnTarget(IsSymbolOnTarget());

			OnTurnEnd();
		}
	}
}

// Functions
void ASymbolDisplay::Turn()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASymbolDisplay %s - Turn"), *GetName());
	}
	
	bIsTurning = true;

	OnTurnStart();
}

void ASymbolDisplay::TurningAnimation(const float DeltaTime)
{
	ElapsedTime += DeltaTime;

	FRotator NewRotation = FMath::Lerp(InitialRotation, TargetRotation, ElapsedTime / TurnDuration);

	SymbolDisplayMesh->SetRelativeRotation(NewRotation);
}

void ASymbolDisplay::SetNextTargetRotation(const uint8 Offset)
{
	InitialRotation = TargetRotation;

	float NewPitch = FMath::Fmod(InitialRotation.Pitch + OffsetRotation.Pitch * Offset, 360.0f);
	float NewYaw = FMath::Fmod(InitialRotation.Yaw + OffsetRotation.Yaw * Offset, 360.0f);
	float NewRoll = FMath::Fmod(InitialRotation.Roll + OffsetRotation.Roll * Offset, 360.0f);

	TargetRotation = {NewPitch, NewYaw, NewRoll};
}

bool ASymbolDisplay::IsSymbolOnTarget()
{
	return GetCurrentSymbol() == GetTargetSymbol();
}

// Events
void ASymbolDisplay::OnTurnStart_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASymbolDisplay %s - OnTurnStart"), *GetName());
	}
}

void ASymbolDisplay::OnTurnEnd_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASymbolDisplay %s - OnTurnEnd"), *GetName());
	}
}

void ASymbolDisplay::OnTargetReached_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASymbolDisplay %s - OnTargetReached"), *GetName());
	}
}

void ASymbolDisplay::OnTargetUnreached_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASymbolDisplay %s - OnTargetUnreached"), *GetName());
	}
}

// Getters/setters
void ASymbolDisplay::SetCurrentSymbol(ESymbol Value)
{
	if (GetCurrentSymbol() != GetTargetSymbol() && Value == GetTargetSymbol())
	{
		// Symbol display goes from "not on target" to "on target"
		OnTargetReached();
	}
	else if (GetCurrentSymbol() == GetTargetSymbol() && Value != GetTargetSymbol())
	{
		// Symbol display goes from "on target" to "not on target"
		OnTargetUnreached();
	}

	CurrentSymbol = Value;
}

ESymbol ASymbolDisplay::GetCurrentSymbol()
{
	return CurrentSymbol;
}

void ASymbolDisplay::SetTargetSymbol(ESymbol Value)
{
	TargetSymbol = Value;
}

ESymbol ASymbolDisplay::GetTargetSymbol()
{
	return TargetSymbol;
}

void ASymbolDisplay::SetIsOnTarget(bool Value)
{
	bIsOnTarget = Value;
}

bool ASymbolDisplay::IsOnTarget()
{
	return bIsOnTarget;
}

uint8 ASymbolDisplay::GetCurrentSymbolByte()
{
	return (uint8)CurrentSymbol;
}

uint8 ASymbolDisplay::GetTargetSymbolByte()
{
	return (uint8)TargetSymbol;
}

// IInteractable implementation
bool ASymbolDisplay::Interact_Implementation()
{
	if (bIsTurning) { return false; }

	Turn();

	return true;
}
