// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Sound/SoundBase.h"
#include "Door.generated.h"

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door", meta=(AllowPrivateAccess = "true"))
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* DoorMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* FrameMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door", meta=(AllowPrivateAccess = "true"))
	UAudioComponent* Audio = nullptr;

protected:
	// Properties
	/** Sound played when the door is opened. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Door")
	USoundBase* OpenDoorSound = nullptr;

	/** Sound played when the door is closed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Door")
	USoundBase* CloseDoorSound = nullptr;

	// TODO: UnlockDoorSound

	// TODO: LockDoorSound

	/** Target rotation for the door to be opened. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	FRotator OpenRotation = {0.0f, 90.0f, 0.0f};

	/** Target rotation for the door to be closed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	FRotator CloseRotation = {0.0f, 0.0f, 0.0f};

	/** Current rotation of the door. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
	FRotator CurrentRotation = {0.0f, 0.0f, 0.0f};
	
	/** Duration for the door to fully open. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	float OpenDuration = 1.5f;

	/** Duration for the door to fully close. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	float CloseDuration = 1.5f;

	/** Elapsed time since the door started opening/closing. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
	float ElapsedTime = 0.0f;

	/** Whether or not the door is unlocked. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	bool bIsUnlocked = true;

	/** Whether or not the door is open. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
	bool bIsOpen = false;

	/** Whether or not the door is currently opening. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
	bool bIsOpening = false;

	/** Whether or not the door is currently closing. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
	bool bIsClosing = false;

	/** Whether or not debug messages should appear in the output log. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Door", AdvancedDisplay)
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
	
	/** Open the door. */
	UFUNCTION(BlueprintCallable, Category="Door")
	virtual void OpenDoor();

	/** Close the door. */
	UFUNCTION(BlueprintCallable, Category="Door")
	virtual void CloseDoor();

	/** Unlock the door. */
	UFUNCTION(BlueprintCallable, Category="Door")
	virtual void UnlockDoor();

	/** Lock the door. */
	UFUNCTION(BlueprintCallable, Category="Door")
	virtual void LockDoor();

	// Events
	/** Event called when the door is opened. */
	UFUNCTION(BlueprintNativeEvent, Category="Door")
	void OnDoorOpened();

	/** Event called when the door is closed. */ 
	UFUNCTION(BlueprintNativeEvent, Category="Door")
	void OnDoorClosed();

	/** Event called when the door is unlocked. */
	UFUNCTION(BlueprintNativeEvent, Category="Door")
	void OnDoorUnlocked();

	/** Event called when the door is locked. */
	UFUNCTION(BlueprintNativeEvent, Category="Door")
	void OnDoorLocked();

	// IInteractable implementation
	virtual bool Interact_Implementation() override;
};
