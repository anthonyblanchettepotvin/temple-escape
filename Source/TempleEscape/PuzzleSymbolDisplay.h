// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SymbolDisplay.h"
#include "PuzzleCondition.h"
#include "PuzzleSymbolDisplay.generated.h"

/**
 * 
 */
UCLASS()
class TEMPLEESCAPE_API APuzzleSymbolDisplay : public ASymbolDisplay, public IPuzzleCondition
{
	GENERATED_BODY()

protected:
	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzle")
	ESymbol TargetSymbol = ESymbol::S_Triangle;

	UPROPERTY()
	TArray<AActor*> RegisteredPuzzles;

	// Getters/setters
	UFUNCTION(BlueprintCallable)
	virtual void SetTargetSymbol(ESymbol Value);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual ESymbol GetTargetSymbol();

	// Functions
	UFUNCTION(BlueprintCallable, Category="Puzzle")
	virtual bool IsSymbolOnTarget();

	// Getters/setters override
	virtual void SetCurrentSymbol(ESymbol Value) override;

	// IPuzzleCondition implementation
	virtual bool Evaluate_Implementation() override;

	virtual bool NotifyPuzzleStateChanged_Implementation() override;

	virtual bool RegisterPuzzle_Implementation(AActor* Puzzle) override;

	virtual bool UnregisterPuzzle_Implementation(AActor* Puzzle) override;
};
