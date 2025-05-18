// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Map.h"

#include "CameraPosition.generated.h"


// Needs these specific values for reciprocity (4-val) to be the opposite dir
UENUM(BlueprintType)
enum class CameraDirection : uint8 {
	DOWN = 0   UMETA(DisplayName = "DOWN"),
	LEFT = 1   UMETA(DisplayName = "LEFT"),
	RIGHT = 2  UMETA(DisplayName = "RIGHT"),
	UP = 3     UMETA(DisplayName = "UP")
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRUDEMO_API UCameraPosition : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UCameraPosition();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	FString stateLabel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Connection")
	CameraDirection connectionInputDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Connection")
	AActor* connectedCameraPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Runtime Connection List")
	//UPROPERTY(meta=(HideInDetailPanel))
	TMap< CameraDirection, UCameraPosition*> connectionsList;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void InitConnections();
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	int bindPath(CameraDirection dir, UCameraPosition* bindPos);
};
