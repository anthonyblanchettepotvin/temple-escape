// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#include "InteractComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Interactable.h"

#define DEBUG true
#define TICK_DEBUG false


// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!FindInputComponent()) { return; }

	SetupInputComponent();

	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("InteractComponent on %s : Initialized."), *GetOwner()->GetName());
	#endif
}


bool UInteractComponent::FindInputComponent()
{
	InputComponent = GetOwner()->InputComponent;

	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("InteractComponent on %s : Input component required."), *GetOwner()->GetName());

		return false;
	}
	else
	{	
		#if DEBUG
		UE_LOG(LogTemp, Warning, TEXT("InteractComponent on %s : Input component found."), *GetOwner()->GetName());
		#endif

		return true;
	}
}


void UInteractComponent::SetupInputComponent()
{
	if (InputComponent)
	{
		InputComponent->BindAction("Interact", IE_Pressed, this, &UInteractComponent::Interact);
	}
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!InputComponent) { return; }

	FetchPlayerViewPoint();
	CalculateInteractLocation();
}


void UInteractComponent::FetchPlayerViewPoint()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
}


void UInteractComponent::CalculateInteractLocation()
{
	InteractLocation = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	#if TICK_DEBUG
	UE_LOG(LogTemp, Warning, TEXT("InteractComponent on %s : InteractLocation : %s"), *GetOwner()->GetName(), *InteractLocation.ToString());
	#endif
}


void UInteractComponent::Interact()
{
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("InteractComponent on %s : Interact attempt."), *GetOwner()->GetName());
	#endif

	FHitResult Hit;
	
	if (CheckForInteractableWithinRange(Hit))
	{	
		#if DEBUG
		UE_LOG(LogTemp, Warning, TEXT("InteractComponent on %s : Object %s is within reach."), *GetOwner()->GetName(), *(Hit.GetActor()->GetName()));
		#endif
		
		if (Hit.GetActor()->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{	
			#if DEBUG
			UE_LOG(LogTemp, Warning, TEXT("InteractComponent on %s : Interacting with %s."), *GetOwner()->GetName(), *(Hit.GetActor()->GetName()));
			#endif

			IInteractable::Execute_Interact(Hit.GetActor());
		}
		else
		{
			#if DEBUG
			UE_LOG(LogTemp, Error, TEXT("InteractComponent on %s : Object %s doesn't implement IInteractable."), *GetOwner()->GetName(), *(Hit.GetActor()->GetName()));
			#endif
		}
	}
}


bool UInteractComponent::CheckForInteractableWithinRange(FHitResult& OutHit)
{
	return GetWorld()->LineTraceSingleByObjectType(
		OutHit,
		PlayerViewPointLocation,
		InteractLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel1),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);
}
