// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "OptionDisplay.generated.h"

/**
 * Struct that encapsulate the information about an option of OptionDisplay.
 */
USTRUCT(BlueprintType)
struct TEMPLEESCAPE_API FDisplayOption
{
	GENERATED_USTRUCT_BODY()

public:
	/** The display option's name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString OptionName;
};

/**
 * OptionDisplay is the base class for any symbol display that can be turned and displays a symbol.
 */
UCLASS()
class TEMPLEESCAPE_API AOptionDisplay : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOptionDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OptionDisplay, meta = (AllowPrivateAccess = "true"))
		USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OptionDisplay, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* OptionDisplayMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OptionDisplay, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh = nullptr;

protected:
	// Properties
	/** The list of options of the option display. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OptionDisplay)
		TArray<FDisplayOption> Options;

	/** Current option the option display is on. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OptionDisplay, meta = (ClampMin = 0))
		int CurrentOptionIndex = 0;

	/** Next option the option display is on. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OptionDisplay, AdvancedDisplay, meta = (ClampMin = 0))
		int NextOptionIndex = 0;

	/** Previous option the option display is on. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OptionDisplay, AdvancedDisplay, meta = (ClampMin = 0))
		int PreviousOptionIndex = 0;

	/** Target option the option display should be. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OptionDisplay, meta = (ClampMin = 0))
		int TargetOptionIndex = 0;

	/** Time it takes for the option display to change option. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OptionDisplay)
		float TurnDuration = 1.0f;

	/** Elapsed time since the option display started turning. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OptionDisplay)
		float ElapsedTime = 0.0f;

	/** Initial rotation when the option display started to change option. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OptionDisplay)
		FRotator InitialRotation = { 0.0f, 0.0f, 0.0f };

	/** Target rotation for the option display to change option. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OptionDisplay)
		FRotator TargetRotation = { 0.0f, 0.0f, 0.0f };

	/** Offset rotation to add to the initial rotation to create the target rotation. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OptionDisplay)
		FRotator OffsetRotation = { 0.0f, 0.0f, 0.0f };

	/** Whether or not the option display is turning. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OptionDisplay)
		bool bIsTurning = false;

	/** Whether or not the option display is on target. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OptionDisplay)
		bool bIsOnTarget = false;

	/** Whether or not debug messages should appear in the output log. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OptionDisplay, AdvancedDisplay)
		bool bDebug = false;

	// Getters/setters
	UFUNCTION(BlueprintCallable)
		virtual void SetCurrentOption(int Value);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		virtual int GetCurrentOption();

	UFUNCTION(BlueprintCallable, Category = OptionDisplay)
		virtual int GetNextOption();

	UFUNCTION(BlueprintCallable, Category = OptionDisplay)
		virtual int GetPreviousOption();

	UFUNCTION(BlueprintCallable)
		virtual void SetTargetOption(int Value);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		virtual int GetTargetOption();

	UFUNCTION(BlueprintCallable)
		virtual void SetIsOnTarget(bool Value);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		virtual bool IsOnTarget();

	// Functions
	/** Turn the option display. */
	UFUNCTION(BlueprintCallable, Category = OptionDisplay)
		virtual void Turn();

	/** Create the option display's turning animation using linear interpolation.
	 * @param DeltaTime The time between the previous and the current frame
	 */
	UFUNCTION(BlueprintCallable, Category = OptionDisplay)
		virtual void TurningAnimation(const float DeltaTime);

	/** Set the next target rotation.
	 * @param Offset The offset (in number of options) to add to the next target rotation
	 * @note Also change the initial rotation with the actor's current rotation.
	 */
	UFUNCTION(BlueprintCallable, Category = OptionDisplay)
		virtual void SetNextTargetRotation(const int Offset = 1);

	/** Check whether or not the current option is equal to the target option.
	 * @return True if the current option is equal to the target option, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category = OptionDisplay)
		virtual bool IsOptionOnTarget();

	// Events
	/** Event called when the option display has started turning. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = OptionDisplay)
		void OnTurnStart();

	/** Event called when the option display has finished turning. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = OptionDisplay)
		void OnTurnEnd();

	/** Event called when the option display's target option has been reached. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = OptionDisplay)
		void OnTargetReached();

	/** Event called when the option display's target option is no longer reached. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = OptionDisplay)
		void OnTargetUnreached();

	// IInteractable implementation
	virtual bool Interact_Implementation() override;
};
