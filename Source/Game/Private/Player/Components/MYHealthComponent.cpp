// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Components/MYHealthComponent.h"
#include <GameFramework/Actor.h>
#include <Dev/MYFireDamageType.h>
#include <Dev/MYIceDamageType.h>

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
UMYHealthComponent::UMYHealthComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

// Called when the game starts
void UMYHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UMYHealthComponent::OnTakeAnyDamageHandler);
    }
}

void UMYHealthComponent::OnTakeAnyDamageHandler(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    Health -= Damage;

    if (DamageType)
    {
        if (DamageType->IsA<UMYFireDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("FIRE !!!"));
        }
        else if (DamageType->IsA<UMYIceDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("COLD !!!"));
        }
    }
}
