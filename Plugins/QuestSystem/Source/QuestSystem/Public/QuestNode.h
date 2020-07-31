// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTaskOwnerInterface.h"
#include "QuestNode.generated.h"

UCLASS()
class QUESTSYSTEM_API UQuestNode : public UObject, public IGameplayTaskOwnerInterface
{
	GENERATED_BODY()
	
public:

	UQuestNode();

	virtual UWorld* GetWorld() const override;
};
