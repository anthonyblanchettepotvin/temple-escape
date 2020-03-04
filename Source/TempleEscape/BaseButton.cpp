// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "BaseButton.h"

#define DEBUG true

ABaseButton::ABaseButton()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseButton::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLocation = GetActorLocation();
}

void ABaseButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsPressing && !bIsUnpressing) { return; }

	if (bIsPressing)
	{
		ButtonPressMovement(DeltaTime);

		if (ElapsedTime > PressDuration)
		{
			bIsPressed = true;
			bIsPressing = false;
			ElapsedTime = 0.0f;

			#if DEBUG
			UE_LOG(LogTemp, Warning, TEXT("Button %s : Button pressed."), *GetName());
			#endif

			OnButtonPressed();
		}

		return;
	}

	if (bIsUnpressing)
	{
		ButtonUnpressMovement(DeltaTime);

		if (ElapsedTime > UnpressDuration)
		{
			bIsPressed = false;
			bIsUnpressing = false;
			ElapsedTime = 0.0f;

			#if DEBUG
			UE_LOG(LogTemp, Warning, TEXT("Button %s : Button unpressed."), *GetName());
			#endif

			OnButtonUnpressed();
		}

		return;
	}
}

void ABaseButton::Press()
{
	FVector CurrentLocation = GetActorLocation();

	// TODO: Refactor this bit of code.
	float Distance = FVector::Distance(InitialLocation, InitialLocation - PressedOffset);
	float DistanceLeft = FVector::Distance(CurrentLocation, InitialLocation - PressedOffset);
	float Delta = (1 - (DistanceLeft / Distance)) * PressDuration; // TODO: Also, that variable name doesn't mean anything
	ElapsedTime = Delta;

	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Button %s : Press button."), *GetName());
	#endif

	bIsPressing = true;
	bIsUnpressing = false;
}

void ABaseButton::ButtonPressMovement(const float DeltaTime)
{
	ElapsedTime += DeltaTime;

	FVector NewLocation = FMath::Lerp(InitialLocation, InitialLocation - PressedOffset, ElapsedTime / PressDuration);

	SetActorLocation(NewLocation);
}

void ABaseButton::Unpress()
{
	FVector CurrentLocation = GetActorLocation();

	// TODO: Refactor this bit of code.
	float Distance = FVector::Distance(InitialLocation, InitialLocation - PressedOffset);
	float DistanceLeft = FVector::Distance(InitialLocation, CurrentLocation);
	float Delta = (1 - (DistanceLeft / Distance)) * UnpressDuration; // TODO: Also, that variable name doesn't mean anything
	ElapsedTime = Delta;

	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Button %s : Unpress button."), *GetName());
	#endif

	bIsUnpressing = true;
	bIsPressing = false;
}

void ABaseButton::ButtonUnpressMovement(const float DeltaTime)
{
	ElapsedTime += DeltaTime;

	FVector NewLocation = FMath::Lerp(InitialLocation - PressedOffset, InitialLocation, ElapsedTime / UnpressDuration);

	SetActorLocation(NewLocation);
}

void ABaseButton::OnButtonPressed_Implementation()
{
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Button %s : OnButtonPressed event invoked."), *GetName());
	#endif
}

void ABaseButton::OnButtonUnpressed_Implementation()
{
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Button %s : OnButtonUnpressed event invoked."), *GetName());
	#endif
}

bool ABaseButton::Interact_Implementation()
{
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Button %s : Interaction attempt."), *GetName());
	#endif

	if (bIsPressing)
	{
		Unpress();
	}
	else if (bIsUnpressing)
	{
		Press();
	}
	else if (bIsPressed)
	{
		Unpress();
	}
	else
	{
		Press();
	}

	return true;
}
