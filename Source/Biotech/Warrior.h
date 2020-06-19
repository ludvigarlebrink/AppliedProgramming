// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Warrior.generated.h"

UCLASS()
class BIOTECH_API AWarrior : public ACharacter
{
	GENERATED_BODY()
	
public:	

	AWarrior();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

};
