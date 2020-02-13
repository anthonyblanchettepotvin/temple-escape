// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "GrabberComponent.h"

#define DEBUG false
#define TICK_DEBUG false
#define VISUAL_DEBUG false

void UGrabberComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!FindPhysicsHandleComponent()) { return; }
}

bool UGrabberComponent::FindPhysicsHandleComponent()
{
	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandleComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("GrabberComponent on %s : PhysicsHandle component required."), *GetOwner()->GetName());
		
		return false;
	}
	else
	{
		#if DEBUG
		UE_LOG(LogTemp, Warning, TEXT("GrabberComponent on %s : PhysicsHandle component found."), *GetOwner()->GetName());
		#endif

		return true;
	}
}

void UGrabberComponent::SetupInputComponent()
{
	if (!InputComponent) { return; }

	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabberComponent::Interact);
	InputComponent->BindAction("Grab", IE_Released, this, &UGrabberComponent::Interact);
}

// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandleComponent) { return; }

	if (PhysicsHandleComponent->GrabbedComponent)
	{	
		#if VISUAL_DEBUG
		DrawDebugSphere(GetWorld(), InteractLocation, 10.0f, 16, FColor::Cyan, false, 0.0f, 1);
		#endif

		PhysicsHandleComponent->SetTargetLocation(InteractLocation);
	}
}

void UGrabberComponent::Interact()
{	
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("GrabberComponent on %s : Interaction attempt."), *GetOwner()->GetName());
	#endif

	if (!PhysicsHandleComponent) { return; }
    
    PhysicsHandleComponent->GrabbedComponent ? Release() : Grab();
}

void UGrabberComponent::Grab()
{	
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("GrabberComponent on %s : Grabbing attempt."), *GetOwner()->GetName());
	#endif

	if (!PhysicsHandleComponent) { return; }

    if (PhysicsHandleComponent->GrabbedComponent) { return; }

	FHitResult Hit;
	
	if (CheckForInteractableWithinRange(Hit))
	{	
		#if DEBUG
		UE_LOG(LogTemp, Warning, TEXT("GrabberComponent on %s : Object %s is within reach."), *GetOwner()->GetName(), *(Hit.GetActor()->GetName()));
		#endif

		// PhysicsHandleComponent->SetTargetLocationAndRotation(PlayerViewPointLocation, PlayerViewPointRotation);
	
		PhysicsHandleComponent->GrabComponentAtLocationWithRotation(
			Hit.GetComponent(),
			NAME_None,
			Hit.GetActor()->GetActorLocation(),
			Hit.GetActor()->GetActorRotation()
		);
	}
}

void UGrabberComponent::Release()
{
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("GrabberComponent on %s : Releasing attempt."), *GetOwner()->GetName());
	#endif

	if (!PhysicsHandleComponent) { return; }

    if (!PhysicsHandleComponent->GrabbedComponent) { return; }

	PhysicsHandleComponent->ReleaseComponent();
}
