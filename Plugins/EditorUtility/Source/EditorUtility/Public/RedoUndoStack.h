// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
class EDITORUTILITY_API RedoUndointerface
{
public:
	// pure virtual function
	virtual void Undo() = 0;
	virtual void Redo() = 0;

};
/**
 * 
 */
class EDITORUTILITY_API RedoUndoStack
{
	FString path;
public:
	RedoUndoStack(int size);
	~RedoUndoStack();
private:
	bool firstfull = false;
	TArray<void*> Array;
	//IRedoUndoInterface* array;
	int maxsize = 0;
	int header = 0;
	int num = 0;
public:
	void Push(void* item);
	bool Pop(void*& item);
	DECLARE_DELEGATE(FOnStackevent);
	FOnStackevent Stackemptyevent;
	FOnStackevent Stacknotemptyevent;
};
class EDITORUTILITY_API RedoUndoManager
{
public:
	RedoUndoManager();
	~RedoUndoManager();
public:
	RedoUndoStack* Undostack;
	RedoUndoStack* Redostack;
};