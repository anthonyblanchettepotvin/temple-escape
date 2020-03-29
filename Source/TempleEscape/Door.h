// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Sound/SoundBase.h"
#include "Door.generated.h"

#define Category "Door"

/**
 * Door is the base class for any door that can be opened, closed, unlocked or locked.
 */
UCLASS()
class TEMPLEESCAPE_API ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Category, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Category, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* DoorMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Category, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* FrameMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Category, meta=(AllowPrivateAccess = "true"))
	UAudioComponent* Audio = nullptr;

protected:
	// Properties
	/** Sound played when the door is opened. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Category)
	USoundBase* OpenDoorSound = nullptr;

	/** Sound played when the door is closed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Category)
	USoundBase* CloseDoorSound = nullptr;

	// TODO: UnlockDoorSound

	// TODO: LockDoorSound

	/** Target rotation for the door to be opened. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Category)
	FRotator OpenRotation = {0.0f, 90.0f, 0.0f};

	/** Target rotation for the door to be closed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Category)
	FRotator CloseRotation = {0.0f, 0.0f, 0.0f};

	/** Current rotation of the door. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Category)
	FRotator CurrentRotation = {0.0f, 0.0f, 0.0f};
	
	/** Time it takes for the door to go from opened to closed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Category)
	float OpenDuration = 1.5f;

	/** Time it takes for the door to go from closed to opened. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Category)
	float CloseDuration = 1.5f;

	/** Elapsed time since the door started opening/closing. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Category)
	float ElapsedTime = 0.0f;

	/** Whether or not the door is unlocked. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Category)
	bool bIsUnlocked = true;

	/** Whether or not the door is open. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Category)
	bool bIsOpen = false;

	/** Whether or not the door is currently opening. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Category)
	bool bIsOpening = false;

	/** Whether or not the door is currently closing. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Category)
	bool bIsClosing = false;

	/** Whether or not debug messages should appear in the output log. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Category, AdvancedDisplay)
	bool bDebug = false;

	// Functions
	/** Open the door. */
	UFUNCTION(BlueprintCallable, Category=Category)
	virtual void OpenDoor();

	/** Close the door. */
	UFUNCTION(BlueprintCallable, Category=Category)
	virtual void CloseDoor();

	/** Unlock the door. */
	UFUNCTION(BlueprintCallable, Category=Category)
	virtual void UnlockDoor();

	/** Lock the door. */
	UFUNCTION(BlueprintCallable, Category=Category)
	virtual void LockDoor();
	
	/** Create the door's open movement using linear interpolation.
	 * @param DeltaTime coming from the Tick member function
	 */
	virtual void OpenDoorMovement(const float DeltaTime);

	/** Create the door's close movement using linear interpolation.
	 * @param DeltaTime coming from the Tick member function 
	 */
	virtual void CloseDoorMovement(const float DeltaTime);
	
	/** Play OpenDoorSound when the door is opened. */
	virtual void PlayOpenSound() const;

	/** Play CloseDoorSound when the door is closed. */
	virtual void PlayCloseSound() const;

	/** Calculate the progress of the current animation.
	 * @param StartRotation The start rotation of the current animation
	 * @param EndRotation The end rotation of the current animation
	 * @param CurrentRotation The current rotation of the actor
	 * @return The progress, in percentage, of the current animation
	 */
	float CalculateAnimationProgress(const FRotator& StartRotation, const FRotator& EndRotation, const FRotator& CurrentRotation) const;

	// TODO: PlayUnlockSound()

	// TODO: PlayLockSound()

	// Events
	/** Event called when the door is opened. */
	UFUNCTION(BlueprintNativeEvent, Category=Category)
	void OnDoorOpened();

	/** Event called when the door is closed. */ 
	UFUNCTION(BlueprintNativeEvent, Category=Category)
	void OnDoorClosed();

	/** Event called when the door is unlocked. */
	UFUNCTION(BlueprintNativeEvent, Category=Category)
	void OnDoorUnlocked();

	/** Event called when the door is locked. */
	UFUNCTION(BlueprintNativeEvent, Category=Category)
	void OnDoorLocked();

	// IInteractable implementation
	virtual bool Interact_Implementation() override;
};
