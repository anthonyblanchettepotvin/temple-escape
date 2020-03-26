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
 * 
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Door")
	USoundBase* OpenDoorSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Door")
	USoundBase* CloseDoorSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	FRotator OpenRotation = {0.0f, 90.0f, 0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	FRotator CloseRotation = {0.0f, 0.0f, 0.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
	FRotator InitialRotation = {0.0f, 0.0f, 0.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
	FRotator CurrentRotation = {0.0f, 0.0f, 0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	float OpenDuration = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	float CloseDuration = 1.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
	float ElapsedTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	bool bIsUnlocked = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
	bool bIsOpen = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
	bool bIsOpening = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
	bool bIsClosing = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Door", AdvancedDisplay)
	bool bDebug = false;

	// Functions
	/**
	 * Create the door's open movement using linear interpolation.
	 * @param DeltaTime coming from the Tick member function
	 */
	virtual void OpenDoorMovement(const float DeltaTime);

	/**
	 * Create the door's close movement using linear interpolation.
	 * @param DeltaTime coming from the Tick member function 
	 */
	virtual void CloseDoorMovement(const float DeltaTime);
	
	virtual void PlayOpenSound() const;

	virtual void PlayCloseSound() const;
	
	UFUNCTION(BlueprintCallable, Category="Door")
	virtual void OpenDoor();

	UFUNCTION(BlueprintCallable, Category="Door")
	virtual void CloseDoor();

	UFUNCTION(BlueprintCallable, Category="Door")
	virtual void UnlockDoor();

	UFUNCTION(BlueprintCallable, Category="Door")
	virtual void LockDoor();

	// Events
	UFUNCTION(BlueprintNativeEvent, Category="Door")
	void OnDoorOpened();

	UFUNCTION(BlueprintNativeEvent, Category="Door")
	void OnDoorClosed();

	UFUNCTION(BlueprintNativeEvent, Category="Door")
	void OnDoorUnlocked();

	UFUNCTION(BlueprintNativeEvent, Category="Door")
	void OnDoorLocked();

	// IInteractable implementation
	virtual bool Interact_Implementation() override;
};
