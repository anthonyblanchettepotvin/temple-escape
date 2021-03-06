// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "DoorComponent.generated.h"

// Delegate signatures
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorOpenDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorCloseDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorOpenedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorClosedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorUnlockedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorLockedDelegate);

/** Component that implements a door that can be opened, closed, unlock and locked. */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UDoorComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Functions
	/** Open the door. */
	UFUNCTION(BlueprintCallable, Category = Door)
		virtual void OpenDoor();

	/** Close the door. */
	UFUNCTION(BlueprintCallable, Category = Door)
		virtual void CloseDoor();

	/** Automatically open or close the door based on it's current state. */
	UFUNCTION(BlueprintCallable, Category = Door)
		virtual void OpenCloseDoor();

	/** Unlock the door. */
	UFUNCTION(BlueprintCallable, Category = Door)
		virtual void UnlockDoor();

	/** Lock the door. */
	UFUNCTION(BlueprintCallable, Category = Door)
		virtual void LockDoor();

protected:
	// Properties
	/** The amount of translation or rotation that the animations should do. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Door)
		FRotator AnimationAmount = { 0.0f, 0.0f, 0.0f };

	/** Target rotation for the door to be opened. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Door)
		FRotator OpenRotation = { 0.0f, 0.0f, 0.0f };

	/** Target rotation for the door to be closed. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Door)
		FRotator CloseRotation = { 0.0f, 0.0f, 0.0f };

	/** Time it takes for the door to go from opened to closed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Door)
		float OpenDuration = 1.5f;

	/** Time it takes for the door to go from closed to opened. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Door)
		float CloseDuration = 1.5f;

	/** Elapsed time since the door started opening/closing. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Door)
		float ElapsedTime = 0.0f;

	/** Whether or not the door is unlocked. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Door)
		bool bIsUnlocked = true;

	/** Whether or not the door is open. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Door)
		bool bIsOpen = false;

	/** Whether or not the door is currently opening. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Door)
		bool bIsOpening = false;

	/** Whether or not the door is currently closing. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Door)
		bool bIsClosing = false;

	/** Whether or not debug messages should appear in the output log. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Door, AdvancedDisplay)
		bool bDebug = false;

	// Functions
	/** Create the door's open movement using linear interpolation.
	 * @param DeltaTime coming from the Tick member function
	 */
	virtual void OpenDoorMovement(const float DeltaTime);

	/** Create the door's close movement using linear interpolation.
	 * @param DeltaTime coming from the Tick member function
	 */
	virtual void CloseDoorMovement(const float DeltaTime);

	/** Calculate the progress of the current animation.
	 * @param StartRotation The start rotation of the current animation
	 * @param EndRotation The end rotation of the current animation
	 * @param CurrentRotation The current rotation of the actor
	 * @return The progress, in percentage, of the current animation
	 */
	float CalculateAnimationProgress(const FRotator& StartRotation, const FRotator& EndRotation, const FRotator& CurrentRotation) const;

public:
	// Delegates
	/** Event that happens when the door started opening. */
	UPROPERTY(BlueprintAssignable, Category = Door)
		FOnDoorOpenDelegate OnDoorOpen;

	/** Event that happens when the door started closing. */
	UPROPERTY(BlueprintAssignable, Category = Door)
		FOnDoorCloseDelegate OnDoorClose;

	/** Event that happens when the door is opened. */
	UPROPERTY(BlueprintAssignable, Category = Door)
		FOnDoorOpenedDelegate OnDoorOpened;

	/** Event that happens when the door is closed. */
	UPROPERTY(BlueprintAssignable, Category = Door)
		FOnDoorClosedDelegate OnDoorClosed;

	/** Event that happens when the door is unlocked. */
	UPROPERTY(BlueprintAssignable, Category = Door)
		FOnDoorUnlockedDelegate OnDoorUnlocked;

	/** Event that happens when the door is locked. */
	UPROPERTY(BlueprintAssignable, Category = Door)
		FOnDoorLockedDelegate OnDoorLocked;
};
