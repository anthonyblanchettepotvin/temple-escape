// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "InteractComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabberComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UGrabberComponent : public UInteractComponent
{
	GENERATED_BODY()

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void Interact() override;

	virtual void Grab();
	virtual void Release();

	/** Check if the owner has a PhysicsHandle component. */
	virtual bool FindPhysicsHandleComponent();

	/** Bind the Input component's actions to the corresponding Grabber methods. */
	virtual void SetupInputComponent() override;

private:
	UPhysicsHandleComponent* PhysicsHandleComponent = nullptr;
};
