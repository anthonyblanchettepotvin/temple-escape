// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "BaseButton.h"

ABaseButton::ABaseButton()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	ButtonMesh->SetMobility(EComponentMobility::Movable);
	ButtonMesh->SetCollisionProfileName("Interactable");
	ButtonMesh->SetupAttachment(Root);

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
	FrameMesh->SetMobility(EComponentMobility::Movable);
	FrameMesh->SetupAttachment(Root);
}

void ABaseButton::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentLocation = GetActorLocation();
	PressedLocation = CurrentLocation - TargetOffset;
	UnpressedLocation = CurrentLocation;
}

void ABaseButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsPressing && !bIsUnpressing) { return; }

	if (bIsPressing)
	{
		ButtonPressAnimation(DeltaTime);

		if (ElapsedTime > PressDuration)
		{
			SetIsPressed(true);
			bIsPressing = false;
			ElapsedTime = 0.0f;

			if (bDebug)
			{
				UE_LOG(LogTemp, Warning, TEXT("ABaseButton %s: Button pressed"), *GetName())
			}

			OnButtonPressed();

			if (!bIsToggle)
			{
				Unpress();
			}
		}

		return;
	}

	if (bIsUnpressing)
	{
		ButtonUnpressAnimation(DeltaTime);

		if (ElapsedTime > UnpressDuration)
		{
			SetIsPressed(false);
			bIsUnpressing = false;
			ElapsedTime = 0.0f;

			if (bDebug)
			{
				UE_LOG(LogTemp, Warning, TEXT("ABaseButton %s: Button unpressed"), *GetName())
			}

			OnButtonUnpressed();
		}

		return;
	}
}

// Functions
void ABaseButton::Press()
{
	CurrentLocation = GetActorLocation();
	ElapsedTime = CalculateAnimationProgress(UnpressedLocation, PressedLocation, CurrentLocation) * PressDuration;

	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseButton %s: Press"), *GetName())
	}

	bIsPressing = true;
	bIsUnpressing = false;
}

void ABaseButton::ButtonPressAnimation(const float DeltaTime)
{
	ElapsedTime += DeltaTime;

	FVector NewLocation = FMath::Lerp(UnpressedLocation, PressedLocation, ElapsedTime / PressDuration);

	SetActorLocation(NewLocation);
	CurrentLocation = GetActorLocation();
}

void ABaseButton::Unpress()
{
	CurrentLocation = GetActorLocation();
	ElapsedTime = CalculateAnimationProgress(PressedLocation, UnpressedLocation, CurrentLocation) * UnpressDuration;

	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseButton %s: Unpress"), *GetName())
	}

	bIsUnpressing = true;
	bIsPressing = false;
}

void ABaseButton::ButtonUnpressAnimation(const float DeltaTime)
{
	ElapsedTime += DeltaTime;

	FVector NewLocation = FMath::Lerp(PressedLocation, UnpressedLocation, ElapsedTime / UnpressDuration);

	SetActorLocation(NewLocation);
	CurrentLocation = GetActorLocation();
}

float ABaseButton::CalculateAnimationProgress(const FVector& StartLocation, const FVector& EndLocation, const FVector& CurrentLocation) const
{
	float CompleteAnimationDistance = FVector::Distance(StartLocation, EndLocation);
	float AnimationDistanceLeft = FVector::Distance(CurrentLocation, EndLocation);
	float Progress = 1 - (AnimationDistanceLeft / CompleteAnimationDistance);
	
	return Progress;
}

// Events
void ABaseButton::OnButtonPressed_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseButton %s: OnButtonPressed"), *GetName())
	}
}

void ABaseButton::OnButtonUnpressed_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseButton %s: OnButtonUnpressed"), *GetName())
	}
}

// IInteractable implementatiom
bool ABaseButton::Interact_Implementation()
{
	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseButton %s: Interact"), *GetName())
	}

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

// Getters/setters
void ABaseButton::SetIsPressed(bool Value)
{
	bIsPressed = Value;
}
