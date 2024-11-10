// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Map.h"

#include "CameraPosition.generated.h"



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
	int connectionInputDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Connection")
	AActor* connectedCameraPosition;
	UPROPERTY(VisibleAnywhere, Category = "Runtime Connection List")
	//UPROPERTY(meta=(HideInDetailPanel))
	TMap< FString, UCameraPosition*> connectionsList;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	int bindPath(int dir, UCameraPosition* bindPos);
};
