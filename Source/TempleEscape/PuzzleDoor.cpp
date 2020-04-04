// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved

#include "PuzzleDoor.h"

void APuzzleDoor::BeginPlay()
{
    Super::BeginPlay();
}

void APuzzleDoor::Tick(float DeltaTime)
{
    if (bIsUnlocked || bIsOpening || bIsClosing)
    {
        Super::Tick(DeltaTime);
    }
}

bool APuzzleDoor::UnlockReward_Implementation()
{
    if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("APuzzleDoor %s: UnlockReward"), *GetName());
	}

    UnlockDoor();
    OnRewardUnlocked_Implementation();

    return true;
}

bool APuzzleDoor::LockReward_Implementation()
{
    if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("APuzzleDoor %s: LockReward"), *GetName());
	}

    LockDoor();
    OnRewardLocked_Implementation();

    return true;
}

void APuzzleDoor::OnRewardUnlocked_Implementation()
{
    if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("APuzzleDoor %s: OnRewardUnlocked"), *GetName());
	}
}

void APuzzleDoor::OnRewardLocked_Implementation()
{
    if (bDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("APuzzleDoor %s: OnRewardLocked"), *GetName());
	}
}

bool APuzzleDoor::IsRewardUnlocked_Implementation()
{
    return bIsUnlocked;
}
