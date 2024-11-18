// Fill out your copyright notice in the Description page of Project Settings.


#include "SM_AnimInstance.h"
#include "UObject/ConstructorHelpers.h"

USM_AnimInstance::USM_AnimInstance()
{
    CurrentPawnSpeed = 0.0f;

    static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_Q_MONTAGE
        (TEXT("/Game/SwordMaster/Animations/Skill_Q_Montage.Skill_Q_Montage"));
    if (SKILL_Q_MONTAGE.Succeeded())
    {
        SkillQMontage = SKILL_Q_MONTAGE.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_W_MONTAGE
        (TEXT("/Game/SwordMaster/Animations/Skill_W_Montage.Skill_W_Montage"));
    if (SKILL_W_MONTAGE.Succeeded())
    {
        SkillWMontage = SKILL_W_MONTAGE.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_E_MONTAGE
        (TEXT("/Game/SwordMaster/Animations/Skill_E_Montage.Skill_E_Montage"));
    if (SKILL_E_MONTAGE.Succeeded())
    {
        SkillEMontage = SKILL_E_MONTAGE.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_R_MONTAGE
        (TEXT("/Game/SwordMaster/Animations/Skill_R_Montage.Skill_R_Montage"));
    if (SKILL_R_MONTAGE.Succeeded())
    {
        SkillRMontage = SKILL_R_MONTAGE.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_D_MONTAGE
        (TEXT("/Game/SwordMaster/Animations/Skill_D_Montage.Skill_D_Montage"));
    if (SKILL_D_MONTAGE.Succeeded())
    {
        SkillDMontage = SKILL_D_MONTAGE.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_F_MONTAGE
        (TEXT("/Game/SwordMaster/Animations/Skill_F_Montage.Skill_F_Montage"));
    if (SKILL_F_MONTAGE.Succeeded())
    {
        SkillFMontage = SKILL_F_MONTAGE.Object;
    }
}

void USM_AnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
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

void USM_AnimInstance::PlaySkill(UAnimMontage* SkillMontage)
{
    if (SkillMontage && !Montage_IsPlaying(SkillMontage))
    {
        Montage_Play(SkillMontage);
    }
}
