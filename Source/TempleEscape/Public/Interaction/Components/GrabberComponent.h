// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabberComponent.generated.h"

// Delegate signatures
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGrabSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReleaseSignature);

/** Actor component that allow the owner to grab an actor. */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TEMPLEESCAPE_API UGrabberComponent : public UInteractComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabberComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Functions
	/** Grab the focused actor. */
	UFUNCTION(BlueprintCallable, Category = GrabberComponent)
		virtual void Grab();

	/** Release the grabbed actor. */
	UFUNCTION(BlueprintCallable, Category = GrabberComponent)
		virtual void Release();

protected:
	// Properties
	/** The distance between the player's viewpoint and the grab location. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GrabberComponent)
		float GrabDistance = 75.0f;

	/** The location, perpendicular to the player's viewpoint, at which the grabbed actor is held. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GrabberComponent)
		FVector GrabLocation = { 0.0f, 0.0f, 0.0f };

	/** The actor that is currently grabbed. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GrabberComponent)
		AActor* GrabbedActor = nullptr;

	/** The pointer to the PhysicsHandle component on the owning actor. */
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = GrabberComponent, AdvancedDisplay)
		UPhysicsHandleComponent* PhysicsHandleComponent = nullptr;

	// Functions
	/** Fetch the PhysicsHandle component on the owning actor. */
	virtual void FetchOwnerPhysicsHandleComponent();

	/** Update the grab location. */
	virtual void UpdateGrabLocation();

	/** Update the grabbed actor's transform. */
	virtual void UpdateGrabbedActorTransform();

	// Events
	/** Event that happens when an actor has been grabbed. */
	UPROPERTY(BlueprintAssignable, Category = GrabberComponent)
		FOnGrabSignature OnGrab;

	/** Event that happens when an actor has been released. */
	UPROPERTY(BlueprintAssignable, Category = GrabberComponent)
		FOnReleaseSignature OnRelease;

	// UInteractComponent overrides
	virtual void SetupOwnerInputComponent() override;

	virtual void Interact() override;
};
