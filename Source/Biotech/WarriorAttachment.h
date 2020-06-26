// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarriorAttachment.generated.h"

class AWarrior;

UCLASS()
class BIOTECH_API AWarriorAttachment : public AActor
{
	GENERATED_BODY()
	
public:	

	AWarriorAttachment();

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadWrite)
	AWarrior* Warrior;
};
