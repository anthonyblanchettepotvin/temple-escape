// Copyright © 2019 Anthony Blanchette-Potvin All Rights Reserved


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPLEESCAPE_API UDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category="Door Component")
		virtual void OpenDoor();
	UFUNCTION(BlueprintCallable, Category="Door Component")
		virtual void CloseDoor();
	virtual void OpenDoorMovement(const float DeltaTime);
	virtual void CloseDoorMovement(const float DeltaTime);

	UFUNCTION(BlueprintCallable, Category="Door Component")
		virtual bool IsOpen() const;
	UFUNCTION(BlueprintCallable, Category="Door Component")
		virtual bool IsOpening() const;
	UFUNCTION(BlueprintCallable, Category="Door Component")
		virtual bool IsClosing() const;

private:
	FRotator InitialRotation;
	FRotator CurrentRotation;
	float ElapsedTime = 0.0f;
	bool bIsOpen = false;
	bool bIsOpening = false;
	bool bIsClosing = false;

	UPROPERTY(EditAnywhere)
		FRotator OpenRotation = {0.0f, 90.0f, 0.0f};
	UPROPERTY(EditAnywhere)
		FRotator CloseRotation = {0.0f, 0.0f, 0.0f};
	UPROPERTY(EditAnywhere)
		float OpenDuration = 1.5f;
	UPROPERTY(EditAnywhere)
		float CloseDuration = 1.5f;
};
