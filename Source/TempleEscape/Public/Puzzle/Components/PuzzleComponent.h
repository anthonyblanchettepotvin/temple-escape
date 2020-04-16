// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzleCondition.h"
#include "PuzzleReward.h"
#include "PuzzleTrigger.h"
#include "PuzzleComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UPuzzleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	/** The puzzle conditions associated with the puzzle.
	 * @note All puzzle conditions must evaluate to true for the puzzle rewards to be unlocked.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Puzzle)
	TArray<AActor*> Conditions;

	/** The puzzle rewards associated with the puzzle.
	 * @note All puzzle conditions must evaluate to true for the puzzle rewards to be unlocked.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Puzzle)
	TArray<AActor*> Rewards;

	/** The puzzle trigger associated with the puzzle.
	 * @note If a puzzle trigger is specified, the puzzle conditions will be evaluated only when the trigger is triggered.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Puzzle)
	AActor* Trigger = nullptr;

	/** Whether or not the puzzle rewards should be unlocked permanently. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Puzzle)
	bool bUnlockRewardsPermanently = false;

	/** Whether or not the puzzle conditions are all met. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Puzzle)
	bool bConditionsMet = false;

	/** Whether or not debug messages should appear in the output log. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Puzzle, AdvancedDisplay)
	bool bDebug = false;

	/** Whether or not all the puzzle conditions' actor implements IPuzzleCondition. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Puzzle, AdvancedDisplay)
	bool bConditionsOK = false;

	/** Whether or not all the puzzle rewards' actor implements IPuzzleReward. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Puzzle, AdvancedDisplay)
	bool bRewardsOK = false;

	// Functions
	/** Check if all the puzzle conditions' actor implements IPuzzleCondition.
	 * @return True if all the puzzle conditions' actor implements IPuzzleCondition, false otherwise
	 * @note Also set bConditionsOK
	 */
	UFUNCTION(BlueprintCallable, Category=Puzzle)
	bool CheckConditionsImplementation();

	/** Check if all the puzzle rewards' actor implements IPuzzleReward.
	 * @return True if all the puzzle rewards' actor implements IPuzzleReward, false otherwise
	 * @note Also set bRewardsOK
	 */
	UFUNCTION(BlueprintCallable, Category=Puzzle)
	bool CheckRewardsImplementation();

	/** Unlock all the puzzle rewards. */
	UFUNCTION(BlueprintCallable, Category=Puzzle)
	void UnlockAllRewards();

	/** Lock all the puzzle rewards. */
	UFUNCTION(BlueprintCallable, Category=Puzzle)
	void LockAllRewards();

	/** Check the result of AreConditionsMet() and act based on its return value.
	 * 
	 * If AreConditionsMet() returns true, unlocks all the rewards and invoke OnConditionsMet().
	 * If AreConditionsMet() returns false, locks all the rewards and invoke OnConditionsUnmet().
	 */
	void ActOnConditionsMet();

	/** Check if all conditions are met.
	 * @return True if all conditions evaluate to true, false otherwise
	 * @note Conditions must implement IPuzzleCondition.
	 */
	UFUNCTION(BlueprintCallable, Category=Puzzle)
	bool AreConditionsMet();

	/** Called when a condition has changed state. */
	UFUNCTION(BlueprintCallable, Category=Puzzle)
	bool ConditionStateChanged(AActor* Condition, bool State);

	/** Called by the trigger when it is triggered.
	 * @return True if the action was successful, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category=Puzzle)
	bool ReactToTrigger();

	/** Subscribe the puzzle to a trigger.
	 * @param wTrigger The trigger to subscribe the puzzle to
	 * @return True if the puzzle has been subscribed to the trigger, false otherwise
	 * @note Trigger must implement IPuzzleTrigger.
	 */
	UFUNCTION(BlueprintCallable, Category=Puzzle)
	bool SubscribeToTrigger(UObject* wTrigger);

	/** Unsubscribe the puzzle from a trigger.
	 * @param wTrigger The trigger to unsubscribe the puzzle from
	 * @return True if the puzzle has been unsubscribed to the trigger, false otherwise
	 * @note Trigger must implement IPuzzle trigger.
	 */
	UFUNCTION(BlueprintCallable, Category=Puzzle)
	bool UnsubscribeFromTrigger(UObject* wTrigger);

	// Events
	/** Event called when all the conditions are met. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Puzzle)
	void OnConditionsMet(); // TODO: This should be a delegate multicast

	/** Event called when all the conditions are unmet. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Puzzle)
	void OnConditionsUnmet(); // TODO: This should be a delegate multicast
};
