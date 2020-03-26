// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "PuzzleReward.h"
#include "PuzzleDoor.generated.h"

/**
 * 
 */
UCLASS()
class TEMPLEESCAPE_API APuzzleDoor : public ADoor, public IPuzzleReward
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// IPuzzleReward implementation
	virtual bool UnlockReward_Implementation() override;

	virtual bool LockReward_Implementation() override;

	virtual void OnRewardUnlocked_Implementation() override;

	virtual void OnRewardLocked_Implementation() override;
	
	virtual bool IsRewardUnlocked_Implementation() override;
};
