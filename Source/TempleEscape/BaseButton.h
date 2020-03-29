// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "BaseButton.generated.h"

#define Category "Button"

/**
 * BaseButton is the base class for any button that can be pressed, unpressed or toggled.
 */
UCLASS()
class TEMPLEESCAPE_API ABaseButton : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseButton();

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
	UStaticMeshComponent* ButtonMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Category, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* FrameMesh = nullptr;

	// TODO: Audio component

protected:
	// Properties
	/** Current location of the actor. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Category)
	FVector CurrentLocation = {0.0f, 0.0f, 0.0f};

	/** Target offset, relative to the current location, for the button to be pressed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Category)
	FVector TargetOffset = {0.0f, 0.0f, 10.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Category)
	FVector PressedLocation = {0.0f, 0.0f, 0.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Category)
	FVector UnpressedLocation = {0.0f, 0.0f, 0.0f};

	/** Time it takes for the button to go from pressed to unpressed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Category)
	float PressDuration = 0.5f;

	/** Time it takes for the button to go from unpressed to pressed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Category)
	float UnpressDuration = 0.5f;

	/** Elapsed time since the button started pressing/unpressing. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Category)
	float ElapsedTime = 0.0f;

	/** Whether or not the button is a toggle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Category)
	bool bIsToggle = false;

	/** Whether or not the button is pressed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetIsPressed, Category=Category)
	bool bIsPressed = false;

	/** Whether or not the button is going from unpressed to pressed. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Category)
	bool bIsPressing = false;

	/** Whether or not the button is going from pressed to unpressed. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Category)
	bool bIsUnpressing = false;

	/** Whether or not debug messages should appear in the output log. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Category, AdvancedDisplay)
	bool bDebug = false;

	// Getters/setters
	UFUNCTION(BlueprintCallable, Category=Category)
	virtual void SetIsPressed(bool Value);

	// Functions
	/** Press the button. */
	UFUNCTION(BlueprintCallable, Category=Category)
	virtual void Press();

	/** Unpress the button. */
	UFUNCTION(BlueprintCallable, Category=Category)
	virtual void Unpress();

	/**
	 * Create the button's press animation using linear interpolation.
	 * @param DeltaTime coming from the Tick member function
	 */
	virtual void ButtonPressAnimation(const float DeltaTime);

	/**
	 * Create the button's unpress animation using linear interpolation.
	 * @param DeltaTime coming from the Tick member function 
	 */
	virtual void ButtonUnpressAnimation(const float DeltaTime);

	/** Calculate the progress of the current animation.
	 * @param StartLocation The start location of the current animation
	 * @param EndLocation The end location of the current animation
	 * @param CurrentLocation The current location of the actor
	 * @return The progress, in percentage, of the current animation
	 */
	float CalculateAnimationProgress(const FVector& StartLocation, const FVector& EndLocation, const FVector& CurrentLocation) const;

	// Events
	/** Event called when the button has been pressed. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Category)
	void OnButtonPressed();

	/** Event called when the button has been unpressed. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Category)
	void OnButtonUnpressed();

	// IInteractable implementation
	virtual bool Interact_Implementation() override;
};
