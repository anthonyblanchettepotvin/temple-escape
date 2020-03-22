// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "SymbolDisplay.generated.h"

UENUM(BlueprintType)
enum class ESymbol : uint8
{
	S_Triangle = 0 UMETA(DisplayName="Triangle"),
	S_Square = 1 UMETA(DisplayName="Square"),
	S_Circle = 2 UMETA(DisplayName="Circle"),
	S_Count = 3 UMETA(Hidden)
};

UCLASS()
class TEMPLEESCAPE_API ASymbolDisplay : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASymbolDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetCurrentSymbol, BlueprintGetter=GetCurrentSymbol, Category="Symbol Display")
	ESymbol CurrentSymbol = ESymbol::S_Triangle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Symbol Display")
	float TurnDuration = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Symbol Display")
	float ElapsedTime = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Symbol Display")
	FRotator StartRotation = {0.0f, 0.0f, 0.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Symbol Display")
	FRotator EndRotation = {0.0f, 0.0f, 0.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Symbol Display")
	bool bIsTurning = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Symbol Display", AdvancedDisplay)
	bool bDebug = false;

	// Getters/setters
	UFUNCTION(BlueprintCallable)
	virtual void SetCurrentSymbol(ESymbol Value);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual ESymbol GetCurrentSymbol();

	// Functions
	/**
	 * TODO: Turn() summary
	 */
	UFUNCTION(BlueprintCallable, Category="Symbol Display")
	virtual void Turn();

	/**
	 * Create the symbol display's turning animation using linear interpolation.
	 * @param DeltaTime The time between the previous and the current frame
	 */
	UFUNCTION(BlueprintCallable, Category="Symbol Display")
	virtual void TurningAnimation(const float DeltaTime);

	/**
	 * Event called when the symbol display has started turning.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Symbol Display")
	void OnTurnStart();

	/**
	 * Event called when the symbol display has finished turning.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Symbol Display")
	void OnTurnEnd();

	// IInteractable implementation
	virtual bool Interact_Implementation() override;
};
