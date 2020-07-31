// Fill out your copyright notice in the Description page of Project Settings.

#include "EdGraphSchema_Quest.h"
#include "QuestSystemEditor.h"
#include "QuestGraphTypes.h"

void UEdGraphSchema_Quest::BreakNodeLinks(UEdGraphNode& TargetNode) const
{

}

void UEdGraphSchema_Quest::BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotification) const
{
}

void UEdGraphSchema_Quest::BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const
{
}

void UEdGraphSchema_Quest::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
}

void UEdGraphSchema_Quest::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	FQuestSystemEditorModule& EditorModule = FModuleManager::GetModuleChecked<FQuestSystemEditorModule>(TEXT("QuestSystemEditor"));
	FQuestGraphNodeClassHelper* ClassCache = EditorModule.ClassCache.Get();

	if (true)
	{
		FCategorizedGraphActionListBuilder TasksBuilder(TEXT("Stages"));

		TArray<FQuestGraphNodeClassData> NodeClasses;
		ClassCache->GatherClasses(UBTTaskNode::StaticClass(), NodeClasses);

		for (const auto& NodeClass : NodeClasses)
		{
			const FText NodeTypeName = FText::FromString(FName::NameToDisplayString(NodeClass.ToString(), false));

			TSharedPtr<FAISchemaAction_NewNode> AddOpAction = UAIGraphSchema::AddNewNodeAction(TasksBuilder, NodeClass.GetCategory(), NodeTypeName, FText::GetEmpty());

			UClass* GraphNodeClass = UBehaviorTreeGraphNode_Task::StaticClass();
			if (NodeClass.GetClassName() == UBTTask_RunBehavior::StaticClass()->GetName())
			{
				GraphNodeClass = UBehaviorTreeGraphNode_SubtreeTask::StaticClass();
			}

			UBehaviorTreeGraphNode* OpNode = NewObject<UBehaviorTreeGraphNode>(ContextMenuBuilder.OwnerOfTemporaries, GraphNodeClass);
			OpNode->ClassData = NodeClass;
			AddOpAction->NodeTemplate = OpNode;
		}

		ContextMenuBuilder.Append(TasksBuilder);
	}
}

void UEdGraphSchema_Quest::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
}

const FPinConnectionResponse UEdGraphSchema_Quest::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	return FPinConnectionResponse();
}

TSharedPtr<FEdGraphSchemaAction> UEdGraphSchema_Quest::GetCreateCommentAction() const
{
	return TSharedPtr<FEdGraphSchemaAction>();
}

int32 UEdGraphSchema_Quest::GetNodeSelectionCount(const UEdGraph* Graph) const
{
	return int32();
}

const FPinConnectionResponse UEdGraphSchema_Quest::CanMergeNodes(const UEdGraphNode* A, const UEdGraphNode* B) const
{
	return FPinConnectionResponse();
}

FLinearColor UEdGraphSchema_Quest::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FLinearColor();
}

FConnectionDrawingPolicy* UEdGraphSchema_Quest::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const
{
	return nullptr;
}

bool UEdGraphSchema_Quest::IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const
{
	return false;
}

int32 UEdGraphSchema_Quest::GetCurrentVisualizationCacheID() const
{
	return int32();
}

void UEdGraphSchema_Quest::ForceVisualizationCacheClear() const
{
}

bool UEdGraphSchema_Quest::ShouldHidePinDefaultValue(UEdGraphPin* Pin) const
{
	return false;
}
