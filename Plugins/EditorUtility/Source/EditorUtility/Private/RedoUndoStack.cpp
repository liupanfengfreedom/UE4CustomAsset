// Fill out your copyright notice in the Description page of Project Settings.


#include "RedoUndoStack.h"

RedoUndoStack::RedoUndoStack(int size)
{
	maxsize = size;
	Array.SetNum(size);
}

RedoUndoStack::~RedoUndoStack()
{
}
void RedoUndoStack::Push(void* item)
{
	//UMyBlueprintFunctionLibrary::CLogtofile("RedoUndoStack::Push");
	if (Array[header])
	{

		delete Array[header];
		//UMyBlueprintFunctionLibrary::CLogtofile("delete Array[header]");
	}
	Array[header++] = item;
	if (num < maxsize)
	{
		num++;
	}
	if (header == maxsize)
	{
		header = 0;
	}
	if (num == 1)
	{
		Stacknotemptyevent.ExecuteIfBound();
	}
}
bool RedoUndoStack::Pop(void*& item)
{
	if (num == 0)
	{
		item = nullptr;
		return false;
	}
	int index = 0;
	if (header == 0)
	{
		index = maxsize - 1;
		header = maxsize - 1;
	}
	else {
		index = --header;
	}
	num--;
	item = Array[index];
	Array[index] = nullptr;
	if (num == 0)
	{
		Stackemptyevent.ExecuteIfBound();
	}
	return true;
}
RedoUndoManager::RedoUndoManager()
{
	Undostack = new RedoUndoStack(120);
	Redostack = new RedoUndoStack(120);

}
RedoUndoManager::~RedoUndoManager()
{
	delete Undostack;
	delete Redostack;
}