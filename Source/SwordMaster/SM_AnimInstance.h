// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SwordMaster.h"
#include "Animation/AnimInstance.h"
#include "SM_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SWORDMASTER_API USM_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	USM_AnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Pawn, Meta=(AllowPrivateAccess=true))
	float CurrentPawnSpeed;
	
};
