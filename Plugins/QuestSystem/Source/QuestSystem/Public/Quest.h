// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Quest.generated.h"

class UEdGraph;

UCLASS()
class QUESTSYSTEM_API UQuest : public UObject
{
	GENERATED_BODY()

public:

	UQuest();

public:
	
	UPROPERTY()
	FText Name;

	UPROPERTY()
	UEdGraph* Graph;
};
