// Fill out your copyright notice in the Description page of Project Settings.
#include "ExCommon.h"
TSharedPtr<DDRecord> DDRecord::RecordInst = NULL;
TSharedPtr<DDRecord> DDRecord::Get()
{
    if (!RecordInst.IsValid())
        RecordInst = MakeShareable(new DDRecord());
    return RecordInst;
}
UExCommon* UExCommon::ExInst = NULL;
UExCommon* UExCommon::Get()
{
    if (!ExInst)
    {
        ExInst = NewObject<UExCommon>();
        ExInst->AddToRoot();
    }
    return ExInst;
}