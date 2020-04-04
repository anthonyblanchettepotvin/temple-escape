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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Puzzle)
	bool Evaluate();

	/** Notify every registered puzzle that the state of this puzzle condition has changed.
	 * @return True if the action was successful, false otherwise
	 */ 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Puzzle)
	bool NotifyPuzzleStateChanged();

	/** Register a puzzle to this puzzle condition.
	 * @param Puzzle The puzzle to register (must implement IPuzzle)
	 * @return True if the puzzle was registered, false otherwise
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Puzzle)
	bool RegisterPuzzle(AActor* Puzzle);
	
	/** Unregister a puzzle from this puzzle condition.
	 * @param Puzzle The puzzle to unregister (must implement IPuzzle)
	 * @return True if the puzzle was unregistered, false otherwise 
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Puzzle)
	bool UnregisterPuzzle(AActor* Puzzle);
};
