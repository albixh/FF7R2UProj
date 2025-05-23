// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "Widgets/SWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Kismet2/StructureEditorUtils.h"
#include "DataObjectEditorUtils.h"
#include "Misc/NotifyHook.h"
#include "Widgets/Input/SComboBox.h"

class IStructureDetailsView;
class SEditableTextBox;
class FStructOnScope;

DECLARE_DELEGATE_OneParam(FOnRowModified, FName /*Row name*/);
DECLARE_DELEGATE_OneParam(FOnRowSelected, FName /*Row name*/);

class SEndRowEditor : public SCompoundWidget
	, public FNotifyHook
	//, public FStructureEditorUtils::INotifyOnStructChanged
	//, public FDataObjectEditorUtils::INotifyOnDataTableChanged
{
public:
	SLATE_BEGIN_ARGS(SEndRowEditor) {}
	SLATE_END_ARGS()

		SEndRowEditor();
	virtual ~SEndRowEditor();

	// FNotifyHook
	virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;
	virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;

	// INotifyOnStructChanged
	//virtual void PreChange(const class UUserDefinedStruct* Struct, FStructureEditorUtils::EStructureEditorChangeInfo Info) override;
	//virtual void PostChange(const class UUserDefinedStruct* Struct, FStructureEditorUtils::EStructureEditorChangeInfo Info) override;

	// INotifyOnDataTableChanged
	//virtual void PreChange(const UEndDataObjectBase* Changed, FDataObjectEditorUtils::EDataTableChangeInfo Info) override;
	//virtual void PostChange(const UEndDataObjectBase* Changed, FDataObjectEditorUtils::EDataTableChangeInfo Info) override;

	FOnRowSelected RowSelectedCallback;

protected:

	TArray<TSharedPtr<FName>> CachedRowNames;
	TSharedPtr<FStructOnScope> CurrentRow;
	TSoftObjectPtr<UEndDataObjectBase> DataObject; // weak obj ptr couldn't handle reimporting
	TSharedPtr<class IStructureDetailsView> StructureDetailsView;
	TSharedPtr<FName> SelectedName;
	TSharedPtr<SComboBox<TSharedPtr<FName>>> RowComboBox;

	void RefreshNameList();
	void CleanBeforeChange();
	void Restore();

	/** Functions for enabling, disabling, and hiding portions of the row editor */
	virtual bool IsMoveRowUpEnabled() const;
	virtual bool IsMoveRowDownEnabled() const;
	virtual bool IsAddRowEnabled() const;
	virtual bool IsRemoveRowEnabled() const;
	virtual EVisibility GetRenameVisibility() const;

	UScriptStruct* GetScriptStruct() const;

	FName GetCurrentName() const;
	FText GetCurrentNameAsText() const;
	FString GetStructureDisplayName() const;
	TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<FName> InItem);
	virtual void OnSelectionChanged(TSharedPtr<FName> InItem, ESelectInfo::Type InSeletionInfo);

	virtual FReply OnAddClicked();
	virtual FReply OnRemoveClicked();
	virtual FReply OnMoveRowClicked(FDataObjectEditorUtils::ERowMoveDirection MoveDirection);
	FReply OnMoveToExtentClicked(FDataObjectEditorUtils::ERowMoveDirection MoveDirection);
	void OnRowRenamed(const FText& Text, ETextCommit::Type CommitType);
	FReply OnResetToDefaultClicked();
	EVisibility GetResetToDefaultVisibility() const;

	void ConstructInternal(UEndDataObjectBase* Changed);

public:

	void Construct(const FArguments& InArgs, UEndDataObjectBase* Changed);

	void SelectRow(FName Name);

	void HandleUndoRedo();

};
