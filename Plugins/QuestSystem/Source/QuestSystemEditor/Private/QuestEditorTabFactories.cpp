#include "QuestEditorTabFactories.h"
#include "QuestEditorTabs.h"

FQuestGraphEditorSummoner::FQuestGraphEditorSummoner(TSharedPtr<FQuestEditor> InQuestEditor, FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback)
	: FDocumentTabFactoryForObjects<UEdGraph>(FQuestEditorTabs::GraphEditorID, InQuestEditor)
	, QuestEditor(InQuestEditor)
	, OnCreateGraphEditorWidget(CreateGraphEditorWidgetCallback)
{
}

void FQuestGraphEditorSummoner::OnTabActivated(TSharedPtr<SDockTab> Tab) const
{
	check(QuestEditor.IsValid());
	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());
	// QuestEditor.Pin()->OnGraphEditorFocused(GraphEditor);
}

void FQuestGraphEditorSummoner::OnTabRefreshed(TSharedPtr<SDockTab> Tab) const
{
	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());
	GraphEditor->NotifyGraphChanged();
}

TAttribute<FText> FQuestGraphEditorSummoner::ConstructTabNameForObject(UEdGraph* DocumentID) const
{
    return TAttribute<FText>(FText::FromString(DocumentID->GetName()));
}

TSharedRef<SWidget> FQuestGraphEditorSummoner::CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const
{
	UE_LOG(LogTemp, Warning, TEXT("Create Tab Body"));

    return OnCreateGraphEditorWidget.Execute(DocumentID);
}

const FSlateBrush* FQuestGraphEditorSummoner::GetTabIconForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const
{
	return FEditorStyle::GetBrush("NoBrush");
}

void FQuestGraphEditorSummoner::SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const
{
	check(QuestEditor.IsValid());
	check(QuestEditor.Pin()->GetQuest());

	// TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());
	// 
	// FVector2D ViewLocation;
	// float ZoomAmount;
	// GraphEditor->GetViewLocation(ViewLocation, ZoomAmount);
	// 
	// UEdGraph* Graph = FTabPayload_UObject::CastChecked<UEdGraph>(Payload);
	// BehaviorTreeEditorPtr.Pin()->GetBehaviorTree()->LastEditedDocuments.Add(FEditedDocumentInfo(Graph, ViewLocation, ZoomAmount));
}
