// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PuzzleCondition.h"
#include "Puzzle.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UPuzzle : public UInterface
{
	GENERATED_BODY()
};

/** Interface that should be implemented by all puzzle actors. */
class TEMPLEESCAPE_API IPuzzle
{
	GENERATED_BODY()

public:
	/** Check if all conditions are met.
	 * @return True if all conditions evaluate to true, false otherwise
	 * @note Conditions must implement IPuzzleCondition.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
	bool AreConditionsMet();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
	bool ConditionStateChanged(AActor* Condition, bool State);

	/** Event called when all the conditions are met. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
	void OnConditionsMet();

	/** Event called when all the conditions are unmet. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
	void OnConditionsUnmet();

	/** Called by the trigger when it is triggered.
	 * @return True if the action was successful, false otherwise
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
	bool ReactToTrigger();

	/** Subscribe the puzzle to a trigger.
	 * @param Trigger The trigger to subscribe the puzzle to
	 * @return True if the puzzle has been subscribed to the trigger, false otherwise
	 * @note Trigger must implement IPuzzleTrigger.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
	bool SubscribeToTrigger(UObject* Trigger);

	/** Unsubscribe the puzzle from a trigger.
	 * @param Trigger The trigger to unsubscribe the puzzle from
	 * @return True if the puzzle has been unsubscribed to the trigger, false otherwise
	 * @note Trigger must implement IPuzzle trigger.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Puzzle")
	bool UnsubscribeFromTrigger(UObject* Trigger);
};
