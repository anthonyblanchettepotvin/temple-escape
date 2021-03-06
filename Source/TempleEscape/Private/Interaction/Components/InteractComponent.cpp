// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "InteractComponent.h"

UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	FetchOwnerInputComponent();
	SetupOwnerInputComponent();
}

void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!InputComponent) { return; }

	FetchPlayerViewPoint();

	UpdateInteractLineStart();
	UpdateInteractLineEnd();
	UpdateFocusedActor();
}

// Functions
void UInteractComponent::FetchOwnerInputComponent()
{
	InputComponent = GetOwner()->InputComponent;

	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("UInteractComponent %s - FetchOwnerInputComponent - Input component not found"), *GetName());

		return;
	}

	if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInteractComponent %s - FetchOwnerInputComponent - Input component found"), *GetName());
	}
}

void UInteractComponent::SetupOwnerInputComponent()
{
	if (!InputComponent) { return; }

	InputComponent->BindAction("Interact", IE_Pressed, this, &UInteractComponent::Interact);
}

void UInteractComponent::FetchPlayerViewPoint()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
}

void UInteractComponent::UpdateInteractLineStart()
{
	InteractLineStart = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * MinInteractDistance;
}

void UInteractComponent::UpdateInteractLineEnd()
{
	InteractLineEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * MaxInteractDistance;
}

void UInteractComponent::UpdateFocusedActor()
{
	bool bHit = false;
	FHitResult Hit;

	bHit = GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewPointLocation,
		InteractLineEnd,
		FCollisionObjectQueryParams(Channel),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	FocusedActor = bHit ? Hit.GetActor() : nullptr;
}

void UInteractComponent::Interact()
{
	if (FocusedActor)
	{	
		if (!FocusedActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			UE_LOG(LogTemp, Error,
				TEXT("UInteractComponent %s - Interact - Actor %s doesn't implement IInteractable"),
				*GetName(),
				*(FocusedActor->GetName()));

			return;
		}
		
		IInteractable::Execute_Interact(FocusedActor);

		if (bDebug)
		{
			UE_LOG(LogTemp, Warning,
				TEXT("UInteractComponent %s - Interact - Interacting with %s"),
				*GetName(),
				*(FocusedActor->GetName()));
		}

		if (OnInteract.IsBound()) { OnInteract.Broadcast(); }
	}
}
