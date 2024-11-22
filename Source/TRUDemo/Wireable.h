// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pin.h"
#include "Wireable.generated.h"

UCLASS()
class TRUDEMO_API AWireable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWireable();

	UFUNCTION(BlueprintPure)
	APin* getPin(int i) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TArray<APin*> pins;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
