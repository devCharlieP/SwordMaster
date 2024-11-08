// Fill out your copyright notice in the Description page of Project Settings.


#include "SM_AnimInstance.h"

USM_AnimInstance::USM_AnimInstance()
{
    CurrentPawnSpeed = 0.0f;
}

void USM_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    auto Pawn = TryGetPawnOwner();
    if(::IsValid(Pawn))
    {
        CurrentPawnSpeed = Pawn->GetVelocity().Size();
    }
}