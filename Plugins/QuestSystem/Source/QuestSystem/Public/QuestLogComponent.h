// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestLogComponent.generated.h"

class UQuest;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API UQuestLogComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UQuestLogComponent();

protected:

	UPROPERTY(EditAnywhere)
	bool LogFailedQuests;

	UPROPERTY(EditAnywhere)
	int32 MaxAcceptedQuets;

private:

	UPROPERTY()
	TArray<UQuest*> ActiveQuests;

	UPROPERTY()
	TArray<UQuest*> CompletedQuests;
};
