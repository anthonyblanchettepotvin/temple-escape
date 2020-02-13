// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Interactable.h"
#include "InteractComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere)
	float Reach = 150.0f;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> Channel = ECollisionChannel::ECC_WorldDynamic;

	UInputComponent* InputComponent = nullptr;

	FVector PlayerViewPointLocation = {0.0f, 0.0f, 0.0f};
	FRotator PlayerViewPointRotation = {0.0f, 0.0f, 0.0f};
	FVector InteractLocation = {0.0f, 0.0f, 0.0f};

	/** Check if the owner has an Input component. */
	virtual bool FindInputComponent();

	/** Bind the Input component's actions to the corresponding Grabber methods. */
	virtual void SetupInputComponent();

	/** Calls GetPlayerViewPoint and stores the result in to PlayerViewPointLocation and PlayerViewPointRotation.
	 * Gets called each tick.
	 */
	virtual void FetchPlayerViewPoint();

	/** Calculate the position at which the Grabber will hold the actor. // TODO : Change this comment and function name.
	 * Gets called each tick.
	 */
	virtual void CalculateInteractLocation();

	/** Interact with the first InteractableComponent on the interactable actor. */
	virtual void Interact();

	/** Check if there's a interactable actor within reach.
	 * @param OutHit 	First blocking hit on interactable actor found
	 * @return 			TRUE if any hit on interactable actor is found
	 */
	virtual bool CheckForInteractableWithinRange(FHitResult& OutHit);
};
