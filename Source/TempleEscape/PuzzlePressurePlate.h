// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PressurePlate.h"
#include "PuzzleCondition.h"
#include "PuzzlePressurePlate.generated.h"

/**
 * 
 */
UCLASS()
class TEMPLEESCAPE_API APuzzlePressurePlate : public APressurePlate, public IPuzzleCondition
{
	GENERATED_BODY()
	
protected:
	// Properties
	UPROPERTY()
	TArray<AActor*> RegisteredPuzzles;

	// IPuzzleCondition implementation
	virtual bool Evaluate_Implementation() override;

	virtual bool NotifyPuzzleStateChanged_Implementation() override;

	virtual bool RegisterPuzzle_Implementation(AActor* Puzzle) override;

	virtual bool UnregisterPuzzle_Implementation(AActor* Puzzle) override;

	// Getters/setters override
	virtual void SetTargetWeightReached(bool Value);
};
