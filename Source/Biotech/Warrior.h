// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "Warrior.generated.h"

class AWarlord;

UCLASS()
class BIOTECH_API AWarrior : public AUnit
{
	GENERATED_BODY()
	
public:	

	AWarrior();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadWrite)
	AWarlord* Warlord;

	UPROPERTY(BlueprintReadWrite)
	AActor* ArmyAttachment;
};
