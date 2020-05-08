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
	/** Puzzles registered to this puzzle condition. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Puzzle, AdvancedDisplay)
	TArray<AActor*> RegisteredPuzzles;

	// Getters/setters override
	virtual void SetCurrentSymbol(ESymbol Value) override;

	// IPuzzleCondition implementation
	virtual bool Evaluate_Implementation() override;

	virtual bool NotifyPuzzleStateChanged_Implementation() override;

	virtual bool RegisterPuzzle_Implementation(AActor* Puzzle) override;

	virtual bool UnregisterPuzzle_Implementation(AActor* Puzzle) override;
};
