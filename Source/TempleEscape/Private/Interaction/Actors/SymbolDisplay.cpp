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

	if (Options.Num() == 0)
	{
		UE_LOG(LogTemp, Error,
			TEXT("ASymbolDisplay %s - BeginPlay - There is no options. The display won't be functionnal"),
			*GetName(),
			Options.Num() - 1)

			return;
	}

	if (CurrentOptionIndex > Options.Num() - 1)
	{
		UE_LOG(LogTemp, Error,
			TEXT("ASymbolDisplay %s - BeginPlay - CurrentOptionIndex is greater than the number of options. Value clamped to %i"),
			*GetName(),
			Options.Num() - 1)
	}

	if (TargetOptionIndex > Options.Num() - 1)
	{
		UE_LOG(LogTemp, Error,
			TEXT("ASymbolDisplay %s - BeginPlay - TargetOptionIndex is greater than the number of options. Value clamped to %i"),
			*GetName(),
			Options.Num() - 1)
	}

	FMath::Clamp(CurrentOptionIndex, 0, Options.Num() - 1);
	FMath::Clamp(TargetOptionIndex, 0, Options.Num() - 1);

	OffsetRotation = { 0.0f, (float)360 / Options.Num(), 0.0f};

	SetNextTargetRotation(CurrentOptionIndex);

	SymbolDisplayMesh->SetRelativeRotation(TargetRotation);

	SetNextTargetRotation();

	SetIsOnTarget(IsOptionOnTarget());
}

void ASymbolDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Options.Num() == 0) { return; }

	if (!bIsTurning) { return; }

	if (bIsTurning)
	{
		TurningAnimation(DeltaTime);

		if (ElapsedTime >= TurnDuration)
		{
			bIsTurning = false;
			ElapsedTime = 0.0f;

			SetNextTargetRotation();

			int NewSymbol = (GetCurrentOption() + 1) % Options.Num();

			SetCurrentOption(NewSymbol);
			SetIsOnTarget(IsOptionOnTarget());

			OnTurnEnd();
		}
	}
}

// Functions
void ASymbolDisplay::Turn()
{
	if (Options.Num() == 0) { return; }

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

	float Alpha = ElapsedTime / TurnDuration;
	Alpha = FMath::Clamp<float>(Alpha, 0, 1);

	FRotator NewRotation = FMath::Lerp(InitialRotation, TargetRotation, Alpha);

	SymbolDisplayMesh->SetRelativeRotation(NewRotation);
}

void ASymbolDisplay::SetNextTargetRotation(const int Offset)
{
	InitialRotation = TargetRotation;

	float NewPitch = FMath::Fmod(InitialRotation.Pitch + OffsetRotation.Pitch * Offset, 360.0f);
	float NewYaw = FMath::Fmod(InitialRotation.Yaw + OffsetRotation.Yaw * Offset, 360.0f);
	float NewRoll = FMath::Fmod(InitialRotation.Roll + OffsetRotation.Roll * Offset, 360.0f);

	TargetRotation = {NewPitch, NewYaw, NewRoll};
}

bool ASymbolDisplay::IsOptionOnTarget()
{
	return GetCurrentOption() == GetTargetOption();
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
void ASymbolDisplay::SetCurrentOption(int Value)
{
	if (GetCurrentOption() != GetTargetOption() && Value == GetTargetOption())
	{
		// Symbol display goes from "not on target" to "on target"
		OnTargetReached();
	}
	else if (GetCurrentOption() == GetTargetOption() && Value != GetTargetOption())
	{
		// Symbol display goes from "on target" to "not on target"
		OnTargetUnreached();
	}

	CurrentOptionIndex = Value;
}

int ASymbolDisplay::GetCurrentOption()
{
	return CurrentOptionIndex;
}

void ASymbolDisplay::SetTargetOption(int Value)
{
	TargetOptionIndex = Value;
}

int ASymbolDisplay::GetTargetOption()
{
	return TargetOptionIndex;
}

void ASymbolDisplay::SetIsOnTarget(bool Value)
{
	bIsOnTarget = Value;
}

bool ASymbolDisplay::IsOnTarget()
{
	return bIsOnTarget;
}

// IInteractable implementation
bool ASymbolDisplay::Interact_Implementation()
{
	if (Options.Num() == 0) { return false; }

	if (bIsTurning) { return false; }

	Turn();

	return true;
}
