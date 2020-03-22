// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Puzzle.h"
#include "PuzzleCondition.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UPuzzleCondition : public UInterface
{
	GENERATED_BODY()
};

/** Interface that should be implemented by all puzzle condition actors. */
class TEMPLEESCAPE_API IPuzzleCondition
{
	GENERATED_BODY()

public:
	/** Evaluate if the condition is met or not.
	 * @return True if the condition is met, false otherwise
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
	bool Evaluate();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
	bool NotifyPuzzleStateChanged();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
	bool RegisterPuzzle(AActor* Puzzle);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
	bool UnregisterPuzzle(AActor* Puzzle);
};
