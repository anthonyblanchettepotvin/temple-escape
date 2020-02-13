// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#define DEBUG false
#define TICK_DEBUG false

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	if (!FindPhysicsHandleComponent()) { return; }
	if (!FindInputComponent()) { return; }

	SetupInputComponent();

	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Grabber on %s : Initialized."), *GetOwner()->GetName());
	#endif
}

bool UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandleComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber on %s : PhysicsHandle component required."), *GetOwner()->GetName());
		
		return false;
	}
	else
	{
		#if DEBUG
		UE_LOG(LogTemp, Warning, TEXT("Grabber on %s : PhysicsHandle component found."), *GetOwner()->GetName());
		#endif

		return true;
	}
}

bool UGrabber::FindInputComponent()
{
	InputComponent = GetOwner()->InputComponent;

	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber on %s : Input component required."), *GetOwner()->GetName());

		return false;
	}
	else
	{	
		#if DEBUG
		UE_LOG(LogTemp, Warning, TEXT("Grabber on %s : Input component found."), *GetOwner()->GetName());
		#endif

		return true;
	}
}

void UGrabber::SetupInputComponent()
{
	if (!InputComponent) { return; }

	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandleComponent || !InputComponent) { return; }

	FetchPlayerViewPoint();
	CalculateGrabberLocation();

	if (PhysicsHandleComponent->GrabbedComponent)
	{
		PhysicsHandleComponent->SetTargetLocation(GrabberLocation);
	}
}

void UGrabber::FetchPlayerViewPoint()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
}

void UGrabber::CalculateGrabberLocation()
{
	GrabberLocation = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	#if TICK_DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Grabber on %s : GrabberLocation : %s"), *GetOwner()->GetName(), *GrabberLocation.ToString());
	#endif
}

void UGrabber::Grab()
{	
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Grabber on %s : Grabbing attempt."), *GetOwner()->GetName());
	#endif

	if (!PhysicsHandleComponent) { return; }

	FHitResult Hit;
	
	if (CheckForGrabbableActorWithinReach(Hit))
	{	
		#if DEBUG
		UE_LOG(LogTemp, Warning, TEXT("Grabber on %s : Object %s is within reach."), *GetOwner()->GetName(), *(Hit.GetActor()->GetName()));
		#endif

		PhysicsHandleComponent->GrabComponentAtLocationWithRotation(
			Hit.GetComponent(),
			NAME_None,
			GrabberLocation,
			Hit.GetActor()->GetActorRotation()
		);
	}
}

void UGrabber::Release()
{
	#if DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Grabber on %s : Releasing attempt."), *GetOwner()->GetName());
	#endif

	if (!PhysicsHandleComponent) { return; }

	PhysicsHandleComponent->ReleaseComponent();
}

bool UGrabber::CheckForGrabbableActorWithinReach(FHitResult& OutHit) const
{
	return GetWorld()->LineTraceSingleByObjectType(
		OutHit,
		PlayerViewPointLocation,
		GrabberLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);
}
