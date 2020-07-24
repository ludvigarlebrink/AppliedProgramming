// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "QuestGraph.generated.h"

UCLASS()
class QUESTSYSTEMEDITOR_API UQuestGraph : public UEdGraph
{
	GENERATED_BODY()
	
public:

	virtual void OnCreated();
	virtual void OnLoaded();
	virtual void Initialize();

	virtual void UpdateAsset(int32 UpdateFlags = 0);
	virtual void UpdateVersion();
	virtual void MarkVersion();

	virtual void OnSubNodeDropped();
	virtual void OnNodesPasted(const FString& ImportStr);

	//~ Begin UObject Interface.
	virtual void Serialize(FArchive& Ar) override;
	//~ End UObject Interface.

protected:

	virtual void CollectAllNodeInstances(TSet<UObject*>& NodeInstances);
	virtual bool CanRemoveNestedObject(UObject* TestObject) const;
	virtual void OnNodeInstanceRemoved(UObject* NodeInstance);
};
