// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestGraphNode.h"
#include "EdGraphSchema_Quest.h"

#define LOCTEXT_NAMESPACE "QuestSystemEditor"

void UQuestGraphNode::AutowireNewNode(UEdGraphPin* FromPin)
{
}

void UQuestGraphNode::PostPlacedNewNode()
{
}

void UQuestGraphNode::PrepareForCopying()
{
}

bool UQuestGraphNode::CanDuplicateNode() const
{
    return true;
}

bool UQuestGraphNode::CanUserDeleteNode() const
{
    return true;
}

void UQuestGraphNode::DestroyNode()
{

}

FText UQuestGraphNode::GetTooltipText() const
{
    return LOCTEXT("TooltipTest", "Tooltip Test");
}

void UQuestGraphNode::NodeConnectionListChanged()
{
}

bool UQuestGraphNode::CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const
{
    return DesiredSchema->GetClass()->IsChildOf(UEdGraphSchema_Quest::StaticClass());
}

void UQuestGraphNode::FindDiffs(UEdGraphNode* OtherNode, FDiffResults& Results)
{
}

FString UQuestGraphNode::GetPropertyNameAndValueForDiff(const FProperty* Prop, const uint8* PropertyAddr) const
{
    return FString();
}

#define LOCTEXT_NAMESPACE "QuestSystemEditor"
