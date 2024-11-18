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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skills")
    UAnimMontage* SkillQMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skills")
    UAnimMontage* SkillWMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skills")
    UAnimMontage* SkillEMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skills")
    UAnimMontage* SkillRMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skills")
    UAnimMontage* SkillDMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skills")
    UAnimMontage* SkillFMontage;

    // 특정 스킬 애니메이션을 실행하는 함수
    void PlaySkill(UAnimMontage* SkillMontage);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Pawn, Meta=(AllowPrivateAccess=true))
	float CurrentPawnSpeed;
	
protected:
    virtual void NativeInitializeAnimation() override;
};
