// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Unit.generated.h"

UENUM(BlueprintType)
enum class EGender : uint8
{
	Female		UMETA(DisplayName = "Female"),
	Male		UMETA(DisplayName = "Male"),
};

UCLASS()
class BIOTECH_API AUnit : public ACharacter
{
	GENERATED_BODY()

public:

	AUnit();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	EGender Gender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 Age;
};
