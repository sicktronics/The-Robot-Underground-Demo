// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wire.generated.h"


UENUM()
enum class WireColor { WHITE, BLACK, RED, ORANGE, YELLOW, GREEN, BLUE, BROWN };

UENUM()
enum class WireType { MALE_MALE, MALE_FEMALE, FELMALE_FEMALE, FORK_MALE };


UCLASS()
class TRUDEMO_API AWire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere)
	WireColor color;

	UPROPERTY(VisibleAnywhere)
	WireType type;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
