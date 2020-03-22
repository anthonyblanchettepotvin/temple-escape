// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "SymbolDisplay.h"

ASymbolDisplay::ASymbolDisplay()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASymbolDisplay::BeginPlay()
{
	Super::BeginPlay();

	uint8 Byte = (uint8)CurrentSymbol;
	StartRotation = GetActorRotation();
	float NewYaw = FMath::Fmod(StartRotation.Yaw + 120.0f * Byte, 360.0f);
	EndRotation = {0.0f, NewYaw, 0.0f};

	SetActorRotation(EndRotation);
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

			uint8 Byte = (uint8)CurrentSymbol;
			CurrentSymbol = static_cast<ESymbol>((Byte + 1) % (uint8)ESymbol::S_Count);

			OnTurnEnd();
		}
	}
}

// Functions
void ASymbolDisplay::Turn()
{
	StartRotation = EndRotation;
	float NewYaw = FMath::Fmod(StartRotation.Yaw + 120.0f, 360.0f);
	EndRotation = {0.0f, NewYaw, 0.0f};
	bIsTurning = true;

	OnTurnStart();
}

void ASymbolDisplay::TurningAnimation(const float DeltaTime)
{
	ElapsedTime += DeltaTime;
	float NormalizedAge = ElapsedTime / TurnDuration;
	FRotator NewRotation = FMath::Lerp(StartRotation, EndRotation, NormalizedAge);

	SetActorRotation(NewRotation);
}

void ASymbolDisplay::OnTurnStart_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASymbolDisplay %s : OnTurnStart"), *GetName());
	}
}

void ASymbolDisplay::OnTurnEnd_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASymbolDisplay %s : OnTurnEnd"), *GetName());
	}
}

// Getters/setters
void ASymbolDisplay::SetCurrentSymbol(ESymbol Value)
{
	CurrentSymbol = Value;
}

ESymbol ASymbolDisplay::GetCurrentSymbol()
{
	return CurrentSymbol;
}

// IInteractable implementation
bool ASymbolDisplay::Interact_Implementation()
{
	if (bIsTurning) { return false; }

	Turn();

	return true;
}
