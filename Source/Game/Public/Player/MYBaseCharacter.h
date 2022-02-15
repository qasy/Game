// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MYBaseCharacter.generated.h"

UCLASS()
class GAME_API AMYBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AMYBaseCharacter();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    class USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    class UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    class UMYHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    class UTextRenderComponent* HealthTextComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    class UAnimMontage* DeathAnimMontage;

    void MoveForward(float Amount);

    void MoveSide(float Amount);

    // Sets Character Movement Speed to Sprint values
    void BeginSprint();

    // Sets Character Movement Speed back to default speed values
    void EndSprint();

    // Request for Character to Crouch
    void BeginCrouch();

    // Request for Character to EndCrouch
    void EndCrouch();

    // Action when character dies
    void OnDeath();
    void OnHealthChanged(float Health);

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
