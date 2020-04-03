// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SymbolDisplay.h"
#include "PuzzleCondition.h"
#include "PuzzleSymbolDisplay.generated.h"

/**
 * PuzzleSymbolDisplay is the base class for any symbol display that is part of a puzzle.
 */
UCLASS()
class TEMPLEESCAPE_API APuzzleSymbolDisplay : public ASymbolDisplay, public IPuzzleCondition
{
	GENERATED_BODY()

protected:
	// Properties
	/** Target symbol for the condition to be met. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetTargetSymbol, BlueprintGette=GetTargetSymbol, Category=Puzzle)
	ESymbol TargetSymbol = ESymbol::S_Triangle;

	/** Puzzles registered to this puzzle condition. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Puzzle, AdvancedDisplay)
	TArray<AActor*> RegisteredPuzzles;

	// Getters/setters
	UFUNCTION(BlueprintCallable)
	virtual void SetTargetSymbol(ESymbol Value);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual ESymbol GetTargetSymbol();

	// Functions
	/** Check whether or not the current symbol is equal to the target symbol.
	 * @return True if the current symbol is equal to the target symbol, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category=Puzzle)
	virtual bool IsSymbolOnTarget();

	// Getters/setters override
	virtual void SetCurrentSymbol(ESymbol Value) override;

	// IPuzzleCondition implementation
	virtual bool Evaluate_Implementation() override;

	virtual bool NotifyPuzzleStateChanged_Implementation() override;

	virtual bool RegisterPuzzle_Implementation(AActor* Puzzle) override;

	virtual bool UnregisterPuzzle_Implementation(AActor* Puzzle) override;
};
