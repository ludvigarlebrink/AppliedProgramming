#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class UQuest;

class IQuestEditor : public FAssetEditorToolkit
{
public:

	virtual ~IQuestEditor() { };

	/** Retrieves the current custom asset. */
	virtual UQuest* GetQuest() const = 0;

	/** Set the current custom asset. */
	virtual void SetQuest(UQuest* Quest) = 0;
};
