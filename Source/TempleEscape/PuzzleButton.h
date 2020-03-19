// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BaseButton.h"
#include "Puzzle.h"
#include "PuzzleCondition.h"
#include "PuzzleTrigger.h"
#include "PuzzleButton.generated.h"

/**
 * 
 */
UCLASS()
class TEMPLEESCAPE_API APuzzleButton : public ABaseButton, public IPuzzleCondition, public IPuzzleTrigger
{
	GENERATED_BODY()

private:
	virtual void Press() override;

	virtual bool Evaluate_Implementation() override;
	virtual bool Interact_Implementation() override;

	virtual bool Trigger_Implementation() override;
	virtual bool Subscribe_Implementation(AActor* Puzzle) override;
	virtual bool Unsubscribe_Implementation(AActor* Puzzle) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzle")
	TArray<APuzzleButton*> AdjacentButtons;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Puzzle")
	TArray<AActor*> SubscribedPuzzles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzle", AdvancedDisplay)
	bool bDebug = false;
};
