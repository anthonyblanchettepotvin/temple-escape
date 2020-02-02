// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetOwner()->GetActorRotation().Yaw < TargetYaw)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
		UE_LOG(LogTemp, Warning, TEXT("%f"), GetOwner()->GetActorRotation().Yaw);

		FRotator StartRotation(0.0f, 0.0f, 0.0f);
		FRotator EndRotation(0.0f, TargetYaw, 0.0f);

		CurrDuration += DeltaTime;

		FRotator NewRotation = FMath::Lerp(StartRotation, EndRotation, CurrDuration / OpenDuration);

		GetOwner()->SetActorRotation(NewRotation);
	}
}
