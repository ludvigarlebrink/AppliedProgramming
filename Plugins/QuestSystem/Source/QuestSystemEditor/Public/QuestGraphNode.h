// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "QuestGraphNode.generated.h"

UCLASS()
class QUESTSYSTEMEDITOR_API UQuestGraphNode : public UEdGraphNode
{
	GENERATED_BODY()
	
public:

	//~ Begin UEdGraphNode Interface
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	virtual void PostPlacedNewNode() override;
	virtual void PrepareForCopying() override;
	virtual bool CanDuplicateNode() const override;
	virtual bool CanUserDeleteNode() const override;
	virtual void DestroyNode() override;
	virtual FText GetTooltipText() const override;
	virtual void NodeConnectionListChanged() override;
	virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;
	virtual void FindDiffs(class UEdGraphNode* OtherNode, struct FDiffResults& Results) override;
	virtual FString GetPropertyNameAndValueForDiff(const FProperty* Prop, const uint8* PropertyAddr) const override;
	//~ End UEdGraphNode Interface
};
